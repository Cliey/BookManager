#pragma once
#include <memory>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

namespace BookManager
{
    namespace Entity
    {
        class Person;
        class Publisher;
    }
    namespace Category
    {
        class Category;
    }


    namespace Manager
    {

        class DatabaseManager
        {
        public:
            static std::shared_ptr<DatabaseManager> getDbManager();

            std::vector<BookManager::Entity::Person> deserializePersonTable(SQLite::Database& database, int limit, int offset);
            std::vector<BookManager::Entity::Publisher> deserializePublisherTable(SQLite::Database& database, int limit, int offset);
            std::vector<BookManager::Category::Category> deserializeCategoryTable(SQLite::Database& database, int limit, int offset);
            // Add Book
            // Add Author
            // Add Publisher
            // Add BookSerie
        private:
            DatabaseManager();
            void loadDatabase(SQLite::Database& database);
            // void deserializePersonTable(SQLite::Database& database, int limit, int offset);
            // void deserializeBookTable(SQLite::Database& database, int limit, int offset);
            void createDatabase();
        };

    } // namespace Manager
} // namespace BookManager
