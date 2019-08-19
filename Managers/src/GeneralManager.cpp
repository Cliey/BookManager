#include "Managers/GeneralManager.hpp"
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

namespace BookManager
{
    namespace Manager
    {
        void GeneralManager::startApp()
        {
            registerHandlerFactory();
            SettingsManager = SettingsManager::getSettingsManager();
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
            std::cout << "Load Database...." << std::endl;
        }
    } // namespace Manager
} // namespace BookManager