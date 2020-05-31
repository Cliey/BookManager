#include "Managers/DatabaseManager.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include "BookAbstract/Book.hpp"
#include "Utils/Log.hpp"
#include "EntityTypes/BookSeries.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "Utils/EnumUtils.hpp"
#include "../../Category.hpp"
#include "Managers/Utils/TableDeserializers.hpp"
#include "Managers/Utils/TableDelete.hpp"
#include "Managers/Utils/TableInsert.hpp"
#include "Managers/Utils/TableUpdater.hpp"

namespace BookManager
{
    namespace Manager
    {
        DatabaseManager::DatabaseManager(std::string databaseName)
        {
            databasePath = "./data/" + databaseName;
            LOG_INFO("DataBase Loading.....");
            try
            {
                database = std::make_shared<SQLite::Database>(databasePath, SQLite::OPEN_READWRITE);
                database->exec("PRAGMA foreign_keys = ON");
                this->initTableActionObject();
            }
            catch(const std::exception& e)
            {
                LOG_ERROR("Error occurred while loading the database : {}", e.what())
                createDatabase();
            }

        }

        DatabaseManager::~DatabaseManager() = default;

        std::unique_ptr<TableDeserializers> DatabaseManager::createTableDeserializer(std::shared_ptr<SQLite::Database> database)
        {
            return std::make_unique<TableDeserializers>(database);
        }

        std::unique_ptr<TableInsert> DatabaseManager::createTableInsert(std::shared_ptr<SQLite::Database> database)
        {
            return std::make_unique<TableInsert>(database);
        }
        std::unique_ptr<TableUpdater> DatabaseManager::createTableUpdater(std::shared_ptr<SQLite::Database> database)
        {
            return std::make_unique<TableUpdater>(database);
        }
        std::unique_ptr<TableDelete> DatabaseManager::createTableDelete(std::shared_ptr<SQLite::Database> database)
        {
            return std::make_unique<TableDelete>(database);
        }

        void DatabaseManager::initTableActionObject()
        {
            tableDeserializer = createTableDeserializer(database);
            tableInsert = createTableInsert(database);
            tableUpdater = createTableUpdater(database);
            tableDelete = createTableDelete(database);
        }

        std::vector<BookManager::Entity::Person> DatabaseManager::getPersonVector(int limit, int offset)
        {
            return tableDeserializer->deserializePersonTable(limit, offset);
        }

        std::vector<BookManager::Entity::Person> DatabaseManager::getPersonVector(int limit, int offset, BookManager::Entity::Role role)
        {
            return tableDeserializer->deserializePersonTable(limit, offset, role);
        }

        std::vector<BookManager::Entity::Publisher> DatabaseManager::getPublisherVector(int limit, int offset)
        {
            return tableDeserializer->deserializePublisherTable(limit, offset);
        }

        std::vector<BookManager::Category::Category> DatabaseManager::getCategoryVector(int limit, int offset)
        {
            return tableDeserializer->deserializeCategoryTable(limit, offset);
        }

        std::vector<BookManager::Entity::BookSeries> DatabaseManager::getBookSeriesVector(int limit, int offset)
        {
            return tableDeserializer->deserializeBookSeriesTable(limit, offset);
        }

        std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> DatabaseManager::getBookVector(int limit, int offset)
        {
            return tableDeserializer->deserializeBookTable(limit, offset);
        }

        bool DatabaseManager::updatePerson(BookManager::Entity::Person personToUpdate)
        {
            return tableUpdater->updatePerson(personToUpdate);
        }
        bool DatabaseManager::updatePublisher(BookManager::Entity::Publisher publisherToUpdate)
        {
            return tableUpdater->updatePublisher(publisherToUpdate);
        }
        bool DatabaseManager::updateCategory(BookManager::Category::Category categoryToUpdate)
        {
            return tableUpdater->updateCategory(categoryToUpdate);
        }
        bool DatabaseManager::updateBookSeries(BookManager::Entity::BookSeries bookSeriesToUpdate)
        {
            return tableUpdater->updateBookSeries(bookSeriesToUpdate);
        }
        bool DatabaseManager::updateBook(std::shared_ptr<BookManager::Book::Abstraction::Book> bookToUpdate)
        {
            return tableUpdater->updateBook(bookToUpdate);
        }

        std::tuple<bool, int> DatabaseManager::insertPerson(BookManager::Entity::Person personToAdd)
        {
            return tableInsert->addPerson(personToAdd);
        }
        std::tuple<bool, int> DatabaseManager::insertPublisher(BookManager::Entity::Publisher publisherToAdd)
        {
            return tableInsert->addPublisher(publisherToAdd);
        }
        std::tuple<bool, int> DatabaseManager::insertCategory(BookManager::Category::Category categoryToAdd)
        {
            return tableInsert->addCategory(categoryToAdd);
        }
        std::tuple<bool, int> DatabaseManager::insertBookSeries(BookManager::Entity::BookSeries bookSeriesToAdd)
        {
            return tableInsert->addBookSeries(bookSeriesToAdd);
        }
        std::tuple<bool, int> DatabaseManager::insertBook(std::shared_ptr<BookManager::Book::Abstraction::Book> bookToAdd)
        {
            return tableInsert->addBook(bookToAdd);
        }

        bool DatabaseManager::deletePerson(int personId, bool bypassForeignKey)
        {
            return tableDelete->checkAndDeleteInPersonTable(personId, bypassForeignKey);
        }
        bool DatabaseManager::deletePublisher(int publisherId, bool bypassForeignKey)
        {
            return tableDelete->checkAndDeleteInPublisherTable(publisherId, bypassForeignKey);
        }
        bool DatabaseManager::deleteCategory(int categoryId, bool bypassForeignKey)
        {
            return tableDelete->checkAndDeleteInCategoryTable(categoryId, bypassForeignKey);
        }
        bool DatabaseManager::deleteBookSeries(int bookSeriesId, bool bypassForeignKey)
        {
            return tableDelete->checkAndDeleteInBookSeriesTable(bookSeriesId, bypassForeignKey);
        }
        bool DatabaseManager::deleteBook(int bookId)
        {
            return tableDelete->deleteInBooksTable(bookId);
        }

        void DatabaseManager::createDatabase()
        {
            LOG_INFO("Creating Database...");
            try
            {
                SQLite::Database db(databasePath, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
                LOG_INFO("Creating Publisher Table...");
                db.exec("CREATE TABLE Publishers(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)");

                LOG_INFO("Creating Author Table...");
                db.exec("CREATE TABLE Persons(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                first_name TEXT NOT NULL,\
                                last_name TEXT NOT NULL,\
                                role INTEGER NOT NULL)");

                LOG_INFO("Creating BookSeries Table...");
                db.exec("CREATE TABLE BookSeries(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)");

                LOG_INFO("Creating Category Table...");
                db.exec("CREATE TABLE Categories(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)");

                LOG_INFO("Creating Books Table...");
                db.exec("CREATE TABLE Books(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                type INTEGER NOT NULL /*-- or text ? */, \
                                title TEXT NOT NULL,\
                                /* author */\
                                main_category INTEGER,\
                                /* Subcategory */\
                                publisher INTEGER,\
                                book_serie INTEGER,\
                                published_date TEXT NOT NULL /* (YYYY-MM-DD) */,\
                                purchased_date TEXT /* (YYYY-MM-DD) */,\
                                price REAL CHECK(price > 0),\
                                status INTEGER DEFAULT 0,\
                                is_read BOOLEAN DEFAULT false NOT NULL /* 0 False / 1 True or INTEGER DEFAULT 0 */,\
                                start_reading_date TEXT /* (YYYY-MM-DD) */,\
                                end_reading_date TEXT /* (YYYY-MM-DD) */,\
                                rate INTEGER DEFAULT NULL,\
                                FOREIGN KEY(main_category) REFERENCES Categories(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null,\
                                FOREIGN KEY(publisher) REFERENCES Publishers(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null,\
                                FOREIGN KEY(book_serie) REFERENCES BookSeries(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null)"); // Not finished

                LOG_INFO("Creating Relational Table Books_Persons...");
                db.exec("CREATE TABLE Books_Persons(\
                                bookId INTEGER NOT NULL,\
                                personId INTEGER NOT NULL,\
                                FOREIGN KEY(bookId) REFERENCES Books(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade,\
                                FOREIGN KEY(personId) REFERENCES Persons(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade)");

                LOG_INFO("Creating Relational Table Books_SubCategory...");
                db.exec("CREATE TABLE Books_SubCategories(\
                                bookId INTEGER NOT NULL,\
                                subCategoryId INTEGER NOT NULL,\
                                FOREIGN KEY(bookId) REFERENCES Books(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade,\
                                FOREIGN KEY(subCategoryId) REFERENCES Categories(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade)");

                database = std::make_shared<SQLite::Database>(databasePath);
                this->initTableActionObject();
            }
            catch(const std::exception& e)
            {
                LOG_ERROR("Error occurred while creating the database : {}", e.what())
                std::remove(databasePath.c_str());
                LOG_ERROR("Database has not been created.");
                return;
            }
        }
    } // namespace Manager
} // namespace BookManager
