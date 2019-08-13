#include "Managers/Manager.hpp"
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
        void Manager::startApp()
        {
            registerHandlerFactory();
            loadOption();
            loadDatabase();
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
        {
            nlohmann::json option;
            std::cout << "Loading Option..." << std::endl;
            std::ifstream file("./data/options.json");
            if(file.is_open())
            {
                file >> optionJson;
                file.close();
            }
            else
            {
                file.close();
                std::cout << "First Launch of the app, init default option" << std::endl;
                setDefaultOption();
                return;
            }

            std::cout << "Option loaded : " << std::endl;
            std::cout << std::setw(4) << optionJson << std::endl;
            // std::cout << std::setw(4) << optionJson["Book"]["showCover"] << std::endl;
            // optionJson["Book"]["showCover"] = false;
            // optionJson["Book"]["sort"] = sorting::price_desc;
            saveOption();
        }

        void Manager::saveOption()
        {
            std::ofstream file("./data/options.json");
            file << std::setw(4) << optionJson << std::endl;
        }

        void Manager::setDefaultOption()
        {
            std::ofstream file;
            file.open("./data/options.json", std::ofstream::out | std::ofstream::app);
            auto defaultOption = R"(
            {
                "Book": {
                    "sort": "name_asc",
                    "showCover": true
                },
                "Person": {
                    "sort": "name_desc"
                },
                "Category": {
                    "sort": "name_desc"
                }
            }
            )"_json;
            file << std::setw(4) << defaultOption << std::endl;
            file.close();
        }

        void Manager::loadDatabase()
        {}
    } // namespace Manager
} // namespace BookManager