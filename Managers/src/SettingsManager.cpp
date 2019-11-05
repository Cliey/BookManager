#include "Managers/SettingsManager.hpp"
#include "Utils/EnumUtils.hpp"
#include "Utils/Exceptions.hpp"
#include "Utils/Loggers.hpp"
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
                try
                {
                    file >> settings;
                }
                catch(const std::exception& e)
                {
                    file.close();
                    std::cout <<"An error in the Setting File occured, do you want to reset Settings?" << '\n';
                    setDefaultSettings();
                    return;
                }
                file.close();

                generalSettings = settings["General"];
                bookSettings = settings["Book"];
                categorySettings = settings["Category"];
                personSettings = settings["Person"];

                saveSettings();

                printSetting();
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

        void SettingsManager::printSetting()
        {
            nlohmann::json settings;
            settings["General"] = generalSettings;
            settings["Book"] = bookSettings;
            settings["Category"] = categorySettings;
            settings["Person"] = personSettings;
            std::cout << std::setw(4) << settings << std::endl;
        }
    } // namespace Manager
} // namespace BookManager