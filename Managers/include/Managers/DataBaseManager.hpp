#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

namespace BookManager
{
    namespace Manager
    {

        class DataBaseManager
        {
        public:
            static DataBaseManager* getDbManager();

        private:
            DataBaseManager();
            void loadDatabase();
            void createDatabase();

            static DataBaseManager* instance;
        };

    } // namespace Manager
} // namespace BookManager
