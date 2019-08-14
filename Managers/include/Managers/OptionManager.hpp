#pragma once
#include <string>
#include <iostream>
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

        class OptionManager
        {
        public:
            static OptionManager *getOptionManager();
            void saveOption();
            void getOption(std::string);
            template<typename T>
            T getOptionTVar(nlohmann::json&, char const*);
            template<typename T, typename U = char const*, typename... Args>
            T getOptionTVar(nlohmann::json&, U, Args...);
            void printOption();
        private:
            OptionManager();
            void loadOption();
            void setDefaultOption();
            bool isOptionExist(std::string);
            bool isOptionExist(nlohmann::json&, nlohmann::json::iterator&);

            static OptionManager *instance;
            nlohmann::json optionJson;
        };

        template<typename T>
        T OptionManager::getOptionTVar(nlohmann::json& json, char const* field)
        {
            if (auto foundValue = json.find(field);
                isOptionExist(json, foundValue))
            {
                // if(foundValue->is_structured())
                // {
                //     return T();
                // }
                return *foundValue;
                /*
                marche pas, a voir c omment checker le type du champ, value_t, mais  enum propre a Json
                isValidData<T>(foundValue) -> dedans on specialise pour chaque
                if(typeid(T) == typeid(*foundValue))
                {
                    return *foundValue;
                }
                std::cout << "ERROR Field exist but the return type is not good!" << std::endl;
                return T();
                */
            }
            std::cout << "ERROR Field doesn't exist!" << std::endl;
            return T();
        }
        template<typename T, typename U, typename... Args>
        T OptionManager::getOptionTVar(nlohmann::json& json, U firstField, Args... args)
        {
            if (auto foundValue = json.find(firstField);
                isOptionExist(json, foundValue))
            {
                if(foundValue->is_object())
                {
                    return getOptionTVar<T>(json[firstField], args...);
                }
                return *foundValue;
            }
            std::cout << "ERROR Field doesn't exist!" << std::endl;
            return T();
        }
    } // namespace Manager
} // namespace BookManager