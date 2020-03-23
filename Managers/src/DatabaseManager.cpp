#include "Managers/DatabaseManager.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include "BookAbstract/Book.hpp"
#include "Utils/Log.hpp"
#include "EntityTypes/BookSerie.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "Utils/EnumUtils.hpp"
#include "../../Category.hpp"
#include "Managers/Utils/TableDeserializers.hpp"

namespace BookManager
{
    namespace Manager
    {
        std::shared_ptr<DatabaseManager> DatabaseManager::getDbManager()
        {
            static std::shared_ptr<DatabaseManager> instance = nullptr;

            if(!instance)
            {
                instance.reset(new DatabaseManager);
            }
            return instance;
        }

        std::unique_ptr<TableDeserializers> DatabaseManager::createTableDeserializer(std::shared_ptr<SQLite::Database> database)
        {
            return std::make_unique<TableDeserializers>(database);
        }

        DatabaseManager::DatabaseManager()
        {
            LOG_INFO("DataBase Loading.....");
            try
            {
                SQLite::Database db("./data/BookManager.db");
                loadDatabase(db);
                database = std::make_shared<SQLite::Database>(db.getFilename());
                tableDeserializer = createTableDeserializer(database);
            }
            catch(const std::exception& e)
            {
                LOG_ERROR("Error occured while loading the database : {}", e.what())
                createDatabase();
            }

        }

        void DatabaseManager::loadDatabase(SQLite::Database& database)
        {
            LOG_INFO("Loading Database...");
            // Load Perons
            // Load Publishers
            // Load Category
            // Load BookSeries
            // Load Books

        }

        std::vector<BookManager::Entity::Person> DatabaseManager::getPersonVector(int limit, int offset)
        {
            return tableDeserializer->deserializePersonTable(limit, offset);
        }

        std::vector<BookManager::Entity::Publisher> DatabaseManager::getPublisherVector(int limit, int offset)
        {
            return tableDeserializer->deserializePublisherTable(limit, offset);
        }

        std::vector<BookManager::Category::Category> DatabaseManager::getCategoryVector(int limit, int offset)
        {
            return tableDeserializer->deserializeCategoryTable(limit, offset);
        }

        std::vector<BookManager::Entity::BookSerie> DatabaseManager::getBookSerieVector(int limit, int offset)
        {
            return tableDeserializer->deserializeBookSerieTable(limit, offset);
        }

        std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> DatabaseManager::getBookVector(int limit, int offset)
        {
            return tableDeserializer->deserializeBookTable(limit, offset);
        }

        void DatabaseManager::createDatabase()
        {
            LOG_INFO("Creating Database...");
            try
            {
                SQLite::Database db("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
                LOG_INFO("Creating Publisher Table...");
                db.exec("CREATE TABLE Publishers(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)"); // OK

                LOG_INFO("Creating Author Table...");
                db.exec("CREATE TABLE Persons(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                firstName TEXT NOT NULL,\
                                lastName TEXT NOT NULL,\
                                role INTEGER NOT NULL)"); // OK

                LOG_INFO("Creating BookSeries Table...");
                db.exec("CREATE TABLE BookSeries(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)"); // add BookVector ? BookId Vector ?

                LOG_INFO("Creating Category Table...");
                db.exec("CREATE TABLE Category(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)"); // OK

                LOG_INFO("Creating Books Table...");
                db.exec("CREATE TABLE Books(\
                                id INT PRIMARY KEY NOT NULL,\
                                type INT NOT NULL /*-- or text ? */, \
                                title TEXT NOT NULL,\
                                /* author */\
                                mainCategoryId INT,\
                                /* Subcategory */\
                                publisherId INT,\
                                bookSerieId INT,\
                                publishedDate TEXT NOT NULL /* (YYYY-MM-DD) */,\
                                purchasedDate TEXT /* (YYYY-MM-DD) */,\
                                price REAL CHECK(price > 0),\
                                status INT DEFAULT 0,\
                                isRead BOOLEAN DEFAULT false NOT NULL /* 0 False / 1 True or INT DEFAULT 0 */,\
                                startReadingDate TEXT /* (YYYY-MM-DD) */,\
                                endReadingDate TEXT /* (YYYY-MM-DD) */,\
                                rate INT DEFAULT NULL,\
                                FOREIGN KEY(mainCategoryId) REFERENCES Category(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null,\
                                FOREIGN KEY(publisherId) REFERENCES Publishers(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null,\
                                FOREIGN KEY(bookSerieId) REFERENCES BookSeries(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null)"); // Not finished

                LOG_INFO("Creating Relational Table Books_Persons...");
                db.exec("CREATE TABLE Books_Persons(\
                                bookId INT NOT NULL,\
                                personId INT NOT NULL,\
                                FOREIGN KEY(bookId) REFERENCES Books(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade,\
                                FOREIGN KEY(personId) REFERENCES Persons(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade)"); // OK

                LOG_INFO("Creating Relational Table Books_SubCategory...");
                db.exec("CREATE TABLE Books_SubCategory(\
                                bookId INT NOT NULL,\
                                subCategoryId INT NOT NULL,\
                                FOREIGN KEY(bookId) REFERENCES Books(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade,\
                                FOREIGN KEY(subCategoryId) REFERENCES Category(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade)"); // OK

                database = std::make_shared<SQLite::Database>(db.getFilename());
                tableDeserializer = createTableDeserializer(database);
            }
            catch(const std::exception& e)
            {
                LOG_ERROR("Error occured while creating the database : {}", e.what())
                std::remove("./data/BookManager.db");
                LOG_ERROR("Database has not been created.");
                return;
            }


        }

    } // namespace Manager
} // namespace BookManager
