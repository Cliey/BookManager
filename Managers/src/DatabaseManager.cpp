#include "Managers/DatabaseManager.hpp"
#include <iostream>

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
            // loadDatabase();
            std::cout << "DataBase Loading....." << std::endl;
        }

        void DatabaseManager::loadDatabase()
        {}

        void DatabaseManager::createDatabase()
        {}

    } // namespace Manager
} // namespace BookManager
