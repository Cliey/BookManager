#include "Managers/SettingsManager.hpp"
#include <fstream>
#include <iomanip>

namespace BookManager
{
    namespace Manager
    {

        std::shared_ptr<SettingsManager> SettingsManager::getSettingsManager()
        {
            static std::shared_ptr<SettingsManager> instance = nullptr;

            if(!instance)
            {
                instance.reset(new SettingsManager());
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
            std::cout << std::setw(4) << settingsJson << std::endl;
            saveSettings();
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
                    errorStr << "Error Field [\"" << field << "\"] exist but the return type (nlohmann::json) is not good!";
                    throw Utils::Exceptions::E_TypeError(errorStr.str());
                }

                try {
                    return *foundValue;
                }
                catch(const std::exception& e)
                {
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