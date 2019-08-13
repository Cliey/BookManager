#pragma once
#include "json/json.hpp"

namespace BookManager
{
    namespace Manager
    {
        enum sorting
        {
            name_desc, name_asc, price_desc, price_asc
        };
        // map sorting values to JSON as strings
        NLOHMANN_JSON_SERIALIZE_ENUM( sorting, {
            {name_desc, "name_desc"},
            {name_asc, "name_asc"},
            {price_desc, "price_desc"},
            {price_asc, "price_asc"},
        })

        class Manager
        {
        public:
            Manager() = default;
            void startApp();
            void saveOption();
        private:
            void registerHandlerFactory();
            void loadOption();
            void setDefaultOption();
            void loadDatabase();

            nlohmann::json optionJson;
        };
    } // namespace Manager
} // namespace BookManager