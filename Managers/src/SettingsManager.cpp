#include "Managers/SettingsManager.hpp"
#include "Utils/EnumUtils.hpp"
#include "Utils/Exceptions.hpp"
#include <nlohmann_json/json.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>

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
            std::cout << "Loading Settings..." << std::endl;
            std::ifstream file("./data/Settings.json");
            if(file.is_open())
            {
                nlohmann::json settings;
                file >> settings;
                try
                {
                    generalSettings = settings["General"];
                    bookSettings = settings["Book"];
                    categorySettings = settings["Category"];
                    personSettings = settings["Person"];
                }
                catch(const nlohmann::json::exception& e)
                {
                    file.close();
                    std::cout << "Error in the Setting file, setting default Value" << std::endl;
                    // Ask if we want to reset all Settings or just the field that caused the problem
                    // setDefaultSettings();
                    return;
                }

                std::cout << "Settings loaded : " << std::endl;
                std::cout << std::setw(4) << settings << std::endl;
                file.close();
            }
            else
            {
                file.close();
                std::cout << "First Launch of the app, init default Settings" << std::endl;
                setDefaultSettings();
            }
        }

        void SettingsManager::saveSettings()
        {
            nlohmann::json settings;
            settings["General"] = generalSettings;
            settings["Book"] = bookSettings;
            settings["Category"] = categorySettings;
            settings["Person"] = personSettings;
            std::ofstream file("./data/Settings.json");
            file << std::setw(4) << settings << std::endl;
        }

        void SettingsManager::setDefaultSettings()
        {
            std::ofstream file;
            file.open("./data/Settings.json", std::ofstream::out);
            nlohmann::json defaultSettings;
            defaultSettings["General"] = GeneralSettings{};
            defaultSettings["Book"] = BookSettings{};
            defaultSettings["Category"] = CategorySettings{};
            defaultSettings["Person"] = PersonSettings{};

            std::cout << "Settings loaded : " << std::endl;
            std::cout << std::setw(4) << defaultSettings << std::endl;

            file << std::setw(4) << defaultSettings << std::endl;
            file.close();
        }
    } // namespace Manager
} // namespace BookManager