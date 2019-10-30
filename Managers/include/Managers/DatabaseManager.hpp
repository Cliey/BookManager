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

        private:
            DatabaseManager();
            void loadDatabase();
            void createDatabase();
        };

    } // namespace Manager
} // namespace BookManager
