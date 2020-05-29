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
        SettingsManager::SettingsManager(std::string filename)
        {
            this->filePath = "./data/" + filename;
            loadSettings();
        }

        void SettingsManager::loadSettings()
        {
            LOG_INFO("Loading Settings...");
            std::ifstream file(this->filePath);
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
                    LOG_WINDOW("An error in the Setting File occurred, do you want to reset Settings? (If you don't reset it, you won't be able to launch the app)");
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
            std::ofstream file(this->filePath);
            file << std::setw(4) << settings << std::endl;
        }

        void SettingsManager::setDefaultSettings()
        {
            std::ofstream file;
            file.open(this->filePath, std::ofstream::out);
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