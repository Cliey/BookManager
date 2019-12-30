#include "Managers/SettingsManager.hpp"
#include "Utils/EnumUtils.hpp"
#include "Utils/Exceptions.hpp"
#include "Utils/Loggers.hpp"
#include <nlohmann/json.hpp>
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
            LOG_INFO("Loading Settings...");
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
                    LOG_WINDOW("An error in the Setting File occured, do you want to reset Settings? (If you don't reset it, you won't be able to launch the app)");
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
                LOG_INFO("First Launch of the app, init default Settings");
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

            LOG_INFO("Settings loaded : ");
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