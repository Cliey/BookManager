#pragma once
#include "json/json.hpp"

namespace BookManager
{
    namespace Manager
    {

        class OptionManager;

        class GeneralManager
        {
        public:
            GeneralManager() = default;
            void startApp();
            void saveOption();
        private:
            void registerHandlerFactory();
            void loadOption();
            void setDefaultOption();
            void loadDatabase();

            // nlohmann::json optionJson;
            OptionManager* optionManager;
        };
    } // namespace Manager
} // namespace BookManager