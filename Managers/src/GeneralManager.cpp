#include "Managers/GeneralManager.hpp"
#include "Managers/DatabaseManager.hpp"
#include "Managers/SettingsManager.hpp"
#include <memory>
#include <fstream>
#include <iomanip>
#include "MaillonCreation/BookCreationResponsibility.hpp"
#include "MaillonCreation/MaillonCreationBookArtBook.hpp"
#include "MaillonCreation/MaillonCreationBookNovel.hpp"
#include "MaillonCreation/MaillonCreationBookComics.hpp"
#include "MaillonCreation/MaillonCreationBookManga.hpp"
#include "BookFactory/BookFactory.hpp"
#include "Utils/Log.hpp"

namespace BookManager
{
    namespace Manager
    {
        void GeneralManager::startApp()
        {
            registerHandlerFactory();

            try
            {
                settingsManager = std::make_shared<SettingsManager>("Settings.json");
            }
            catch(const std::exception& e)
            {
                std::cout << "XXX -hello" << std::endl;
                std::cerr << e.what() << '\n';
            }

            loadDatabase();
        }

        void GeneralManager::registerHandlerFactory()
        {
            using namespace BookManager::Book;
            BookFactory::append(std::make_unique<Utils::MaillonCreationBookArtBook>());
            BookFactory::append(std::make_unique<Utils::MaillonCreationBookNovel>());
            BookFactory::append(std::make_unique<Utils::MaillonCreationBookComics>());
            BookFactory::append(std::make_unique<Utils::MaillonCreationBookManga>());
        }

        void GeneralManager::loadDatabase()
        {
            LOG_INFO("Load Database....");
            databaseManager = std::make_shared<DatabaseManager>("BookManager.db");
        }

        std::shared_ptr<DatabaseManager> GeneralManager::getDatabaseManager()
        {
            return databaseManager;
        }

        std::shared_ptr<SettingsManager> GeneralManager::getSettingsManager()
        {
            return settingsManager;
        }

    } // namespace Manager
} // namespace BookManager