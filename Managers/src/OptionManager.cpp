#include "Managers/OptionManager.hpp"
#include <fstream>
#include <iomanip>

namespace BookManager
{
    namespace Manager
    {
        OptionManager* OptionManager::instance = nullptr;

        OptionManager* OptionManager::getOptionManager()
        {
            if(!instance)
            {
                instance = new OptionManager;
            }
            return instance;
        }

        OptionManager::OptionManager()
        {
            loadOption();
        }
        void OptionManager::loadOption()
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
            // std::cout << std::setw(4) << optionJson << std::endl;
            // std::string champ{"Book"};
            // std::cout << std::setw(4) << optionJson[champ.c_str()] << std::endl;
            saveOption();

            getOption("Book");
            // std::cout << std::setw(4) << optionJson << std::endl;

            // std::cout << "XX - BookBool = " <<  getOptionTVar<bool>(optionJson, "Book") << std::endl; Marche pas
            std::cout << "XX - showCover = " << std::boolalpha << getOptionTVar<bool>(optionJson, "Book", "showCover") << std::endl;
            std::cout << "XX - Book = " << getOptionTVar<nlohmann::json>(optionJson, "Book") << std::endl;
            optionJson["Book"]["sort"] = sorting::price_desc;
            std::cout << "XX - sort string ? = " <<  optionJson["Book"]["sort"].is_string() << std::endl;
            std::cout << "XX - sort structured ? = " <<  optionJson["Book"]["sort"].is_structured() << std::endl;
            // optionJson["Book"]["showCover"] = false;
            // for (nlohmann::json::iterator it = optionJson["Book"].begin(); it != optionJson["Book"].end(); ++it)
            // {
            //     std::cout << *it << '\n';
            // }
            // for (auto& element : optionJson["Book"].items()) {
            //     std::cout << element.key() << " -> " << element.value() << '\n';
            // }
        }

        void OptionManager::saveOption()
        {
            std::ofstream file("./data/options.json");
            file << std::setw(4) << optionJson << std::endl;
        }

        void OptionManager::setDefaultOption()
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

        void OptionManager::getOption(std::string field)
        {
            if(isOptionExist(field))
            {
                std::cout << std::setw(4) << optionJson[field.c_str()] << std::endl;
                return;
            }
            std::cout << "ERROR : field doesn't exist!" << std::endl;
        }

        bool OptionManager::isOptionExist(std::string field)
        {
            return !(optionJson[field.c_str()].is_null());
        }

        bool OptionManager::isOptionExist(nlohmann::json& json, nlohmann::json::iterator& foundField)
        {
            return foundField != json.end();
        }
        void OptionManager::printOption() // DEBUG FCT
        {
            std::cout << std::setw(4) << optionJson << std::endl;
        }
    } // namespace Manager
} // namespace BookManager