#pragma once
#include <memory>
#include <SQLiteCpp/SQLiteCpp.h>

namespace BookManager
{
    namespace Manager
    {

        class DatabaseManager
        {
        public:
            static std::shared_ptr<DatabaseManager> getDbManager();
            // Add Book
            // Add Author
            // Add Publisher
            // Add BookSerie
        private:
            DatabaseManager();
            void loadDatabase(SQLite::Database& database);
            // void deserializeAuthorTable();
            // void deserializeBookTable();
            void createDatabase();
        };

    } // namespace Manager
} // namespace BookManager
