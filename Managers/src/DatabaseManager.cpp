#include "Managers/DatabaseManager.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include "Utils/Log.hpp"
#include "EntityTypes/Person.hpp"

#include "Utils/EnumUtils.hpp"

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

        DatabaseManager::DatabaseManager()
        {
            LOG_INFO("DataBase Loading.....");
            try
            {
                SQLite::Database database("./data/BookManager.db");
                loadDatabase(database);
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
            // Load BookSeries
            // Load Books

        }

        void DatabaseManager::deserializePersonTable(SQLite::Database& database, int limit, int offset)
        {
            std::vector<BookManager::Entity::Person> personVector;
            SQLite::Statement query(database, "SELECT * FROM Persons LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                int id = query.getColumn("id");
                std::string firstName = query.getColumn("firstName");
                std::string lastName = query.getColumn("lastName");
                BookManager::Entity::Role role{query.getColumn("role").getInt()};
                personVector.emplace_back(BookManager::Entity::Person{id, firstName, lastName, role});
            }

            for(auto person : personVector)
            {
                std::cout << "Person : (" << person.getId() << ") " << person.getFirstName() << " " << person.getLastName() << " in a(n) "
                            << Utils::EnumUtils::roleString(person.getRole()) << std::endl;
            }
        }

        void DatabaseManager::createDatabase()
        {
            LOG_INFO("Creating Database...");
            try
            {
                SQLite::Database database("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
                LOG_INFO("Creating Publisher Table...");
                database.exec("CREATE TABLE Publishers(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)"); // OK

                LOG_INFO("Creating Author Table...");
                database.exec("CREATE TABLE Persons(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                firstName TEXT NOT NULL,\
                                lastName TEXT NOT NULL,\
                                role INTEGER NOT NULL)"); // OK

                LOG_INFO("Creating BookSeries Table...");
                database.exec("CREATE TABLE BookSeries(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)"); // add BookVector ? BookId Vector ?

                LOG_INFO("Creating Category Table...");
                database.exec("CREATE TABLE Category(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL)"); // OK

                LOG_INFO("Creating SubCategory Table...");
                database.exec("CREATE TABLE SubCategory(\
                                id INTEGER PRIMARY KEY NOT NULL,\
                                name TEXT NOT NULL,\
                                categoryId INTEGER,\
                                FOREIGN KEY(categoryId) REFERENCES Category(id)\
                                    ON UPDATE cascade\
                                    ON DELETE set null)"); // OK

                LOG_INFO("Creating Books Table...");
                database.exec("CREATE TABLE Books(\
                                id INT PRIMARY KEY NOT NULL,\
                                /* type INT NOT NULL, -- or text ? */ \
                                title TEXT NOT NULL,\
                                /* author */\
                                categoryId INT,\
                                /* Subcategory */\
                                publisherId INT,\
                                bookSerieId INT,\
                                publishedDate TEXT NOT NULL /* (YYYY-MM-DD) */,\
                                purchasedDate TEXT /* (YYYY-MM-DD) */,\
                                price REAL CHECK(price > 0),\
                                /* statut (integer? 1 a 3 check) */\
                                isRead BOOLEAN DEFAULT false NOT NULL /* 0 False / 1 True or INT DEFAULT 0 */,\
                                startReadingDate TEXT /* (YYYY-MM-DD) */,\
                                endReadingDate TEXT /* (YYYY-MM-DD) */,\
                                rate INT DEFAULT NULL,\
                                FOREIGN KEY(categoryId) REFERENCES Category(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null,\
                                FOREIGN KEY(publisherId) REFERENCES Publishers(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null,\
                                FOREIGN KEY(bookSerieId) REFERENCES BookSeries(id)\
                                        ON UPDATE cascade\
                                        ON DELETE set null)"); // Not finished

                LOG_INFO("Creating Relational Table Books_Persons...");
                database.exec("CREATE TABLE Books_Persons(\
                                bookId INT NOT NULL,\
                                personId INT NOT NULL,\
                                FOREIGN KEY(bookId) REFERENCES Books(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade,\
                                FOREIGN KEY(personId) REFERENCES Persons(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade)"); // OK

                LOG_INFO("Creating Relational Table Books_SubCategory...");
                database.exec("CREATE TABLE Books_SubCategory(\
                                bookId INT NOT NULL,\
                                subCategoryId INT NOT NULL,\
                                FOREIGN KEY(bookId) REFERENCES Books(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade,\
                                FOREIGN KEY(subCategoryId) REFERENCES SubCategory(id)\
                                    ON UPDATE cascade\
                                    ON DELETE cascade)"); // OK
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
