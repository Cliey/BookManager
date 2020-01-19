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

            void deserializePersonTable(SQLite::Database& database, int limit, int offset);
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
