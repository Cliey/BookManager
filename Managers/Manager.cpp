#include "Manager.hpp"
#include <memory>
// #include "MaillonCreation/BookCreationResponsibility.hpp"
#include "BookCreationResponsibility.hpp"
#include "../MaillonCreation/MaillonCreationBookArtBook.hpp"
#include "../MaillonCreation/MaillonCreationBookNovel.hpp"
#include "../MaillonCreation/MaillonCreationBookComics.hpp"
#include "../MaillonCreation/MaillonCreationBookManga.hpp"
#include "../Book/Factory/BookFactory.hpp"

namespace BookManager
{
    namespace Manager
    {
        void Manager::startApp()
        {
            registerHandlerFactory();
            loadOption();
        }

        void Manager::registerHandlerFactory()
        {
            using namespace BookManager::Book;
            BookFactory::append(std::make_unique<Utils::MaillonCreationBookArtBook>());
            BookFactory::append(std::make_unique<Utils::MaillonCreationBookNovel>());
            BookFactory::append(std::make_unique<Utils::MaillonCreationBookComics>());
            BookFactory::append(std::make_unique<Utils::MaillonCreationBookManga>());
        }

        void Manager::loadOption()
        {}

    } // namespace Manager
} // namespace BookManager