#pragma once
#include "json/json.hpp"

namespace BookManager
{
    namespace Manager
    {

        class SettingsManager;

        class GeneralManager
        {
        public:
            GeneralManager() = default;
            void startApp();
            void saveSettings();
        private:
            void registerHandlerFactory();
            void loadSettings();
            void setDefaultSettings();
            void loadDatabase();

            // nlohmann::json SettingsJson;
            SettingsManager* SettingsManager;
        };
    } // namespace Manager
} // namespace BookManager