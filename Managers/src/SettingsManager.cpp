#include "Managers/SettingsManager.hpp"
#include <fstream>
#include <iomanip>

namespace BookManager
{
    namespace Manager
    {
        SettingsManager* SettingsManager::instance = nullptr;

        SettingsManager* SettingsManager::getSettingsManager()
        {
            if(!instance)
            {
                instance = new SettingsManager;
            }
            return instance;
        }

        SettingsManager::SettingsManager()
        {
            loadSettings();
        }
        void SettingsManager::loadSettings()
        {
            nlohmann::json Settings;
            std::cout << "Loading Settings..." << std::endl;
            std::ifstream file("./data/Settings.json");
            if(file.is_open())
            {
                file >> settingsJson;
                file.close();
            }
            else
            {
                file.close();
                std::cout << "First Launch of the app, init default Settings" << std::endl;
                setDefaultSettings();
                return;
            }

            std::cout << "Settings loaded : " << std::endl;
            // std::cout << std::setw(4) << settingsJson << std::endl;
            // std::string champ{"Book"};
            // std::cout << std::setw(4) << settingsJson[champ.c_str()] << std::endl;
            saveSettings();

            // std::cout << std::setw(4) << settingsJson << std::endl;

            // std::cout << "XX - BookBool = " <<  getSettings<bool>(settingsJson, "Book") << std::endl; Marche pas
            std::cout << "XX1 - showCover = " << std::boolalpha << getSettings<bool>(settingsJson, "Book", "showCover") << std::endl;
            // std::cout << "XX - Book = " << getSettings<bool>(settingsJson, "Book") << std::endl;
            std::cout << "XX2 - Book = " << getSettings<nlohmann::json>(settingsJson, "Book") << std::endl;
            auto BookJson = getSettings<nlohmann::json>(settingsJson, "Book");
            std::cout << "XX3 - showCover from Bookjson = " << getSettings<bool>(BookJson, "showCover") << std::endl;
            try {
                std::cout << "XX4 - showCover from Bookjson string = " << getSettings<std::string>(BookJson, "showCover") << std::endl;
            }
            catch(std::exception& e)
            {
                std::cout <<"error catch : " << e.what() << std::endl;
            }

            try {
                std::cout << "XX5 - showCover from Bookjson nlohmann::json = " << getSettings<nlohmann::json>(BookJson, "showCover") << std::endl;
            }
            catch(std::exception& e)
            {
                std::cout <<"error catch : " << e.what() << std::endl;
            }
            std::cout << "XX6 - Book in book = " << getSettings<nlohmann::json>(settingsJson, "Book", "Book") << std::endl;
            settingsJson["Book"]["sort"] = sorting::price_desc;
            std::cout << "XX7 - sort string ? = " <<  settingsJson["Book"]["sort"].is_string() << std::endl;
            std::cout << "XX8 - sort structured ? = " <<  settingsJson["Book"]["sort"].is_structured() << std::endl;

            try {
                std::cout << "XX9 - Book bool = " << getSettings<bool>(settingsJson, "Book") << std::endl;
            }
            catch(std::exception& e)
            {
                std::cout <<"error catch : " << e.what() << std::endl;
            }
            // settingsJson["Book"]["showCover"] = false;
            // for (nlohmann::json::iterator it = settingsJson["Book"].begin(); it != settingsJson["Book"].end(); ++it)
            // {
            //     std::cout << *it << '\n';
            // }
            // for (auto& element : settingsJson["Book"].items()) {
            //     std::cout << element.key() << " -> " << element.value() << '\n';
            // }
        }

        template<>
        nlohmann::json SettingsManager::getSettings(nlohmann::json& json, char const* field)
        {
            if (auto foundValue = json.find(field);
                isSettingsExist(json, foundValue))
            {
                if(!foundValue->is_structured())
                {
                    std::stringstream errorStr;
                    errorStr << "Error Field [\"" << field << "\"] exist but the return type (nlohmann::json) is not good!" << std::endl;
                    throw std::overflow_error(errorStr.str());
                }

                try {
                    return *foundValue;
                }
                catch(const std::exception& e)
                {
                    // Propagate the exception
                    // std::cout <<"Error catch : " << e.what() << std::endl;
                    throw;
                }
            }
            std::cout << "ERROR Field doesn't exist!" << std::endl;
            return nlohmann::json();
        }

        void SettingsManager::saveSettings()
        {
            std::ofstream file("./data/Settings.json");
            file << std::setw(4) << settingsJson << std::endl;
        }

        void SettingsManager::setDefaultSettings()
        {
            std::ofstream file;
            file.open("./data/Settings.json", std::ofstream::out | std::ofstream::app);
            auto defaultSettings = R"(
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
            file << std::setw(4) << defaultSettings << std::endl;
            file.close();
        }

        bool SettingsManager::isSettingsExist(std::string field)
        {
            return !(settingsJson[field.c_str()].is_null());
        }

        bool SettingsManager::isSettingsExist(nlohmann::json& json, nlohmann::json::iterator& foundField)
        {
            return foundField != json.end();
        }
        void SettingsManager::printSettings() // DEBUG FCT
        {
            std::cout << std::setw(4) << settingsJson << std::endl;
        }
    } // namespace Manager
} // namespace BookManager