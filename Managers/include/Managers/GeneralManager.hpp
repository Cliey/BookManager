#pragma once
#include <memory>

namespace BookManager
{
    namespace Manager
    {

        class SettingsManager;
        class DatabaseManager;

        class GeneralManager
        {
        public:
            GeneralManager() = default;
            void startApp();
            void saveSettings();
            std::shared_ptr<DatabaseManager> getDatabaseManager();

        private:
            void registerHandlerFactory();
            void loadSettings();
            void setDefaultSettings();
            void loadDatabase();

            // nlohmann::json SettingsJson;
            std::shared_ptr<SettingsManager> settingsManager;
            std::shared_ptr<DatabaseManager> databaseManager;
        };
    } // namespace Manager
} // namespace BookManager