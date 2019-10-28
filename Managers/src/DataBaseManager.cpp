#include "Managers/DataBaseManager.hpp"

namespace BookManager
{
    namespace Manager
    {
        DataBaseManager* DataBaseManager::instance = nullptr;

        DataBaseManager* DataBaseManager::getDbManager()
        {
            if(!instance)
            {
                instance = new DataBaseManager;
            }
            return instance;
        }

        DataBaseManager::DataBaseManager()
        {
            // loadDatabase();
        }

        void DataBaseManager::loadDatabase()
        {}

        void DataBaseManager::createDatabase()
        {}

    } // namespace Manager
} // namespace BookManager
