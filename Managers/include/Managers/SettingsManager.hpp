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

        class SettingsManager
        {
        public:
            static SettingsManager *getSettingsManager();
            void saveSettings();
            template<typename T>
            T getSettings(nlohmann::json&, char const*);
            template<typename T, typename U = char const*, typename... Args>
            T getSettings(nlohmann::json&, U, Args...);
            void printSettings();
        private:
            SettingsManager();
            void loadSettings();
            void setDefaultSettings();
            bool isSettingsExist(std::string);
            bool isSettingsExist(nlohmann::json&, nlohmann::json::iterator&);

            static SettingsManager *instance;
            nlohmann::json settingsJson;
        };

        template<typename T>
        T SettingsManager::getSettings(nlohmann::json& json, char const* field)
        {
            if (auto foundValue = json.find(field);
                isSettingsExist(json, foundValue))
            {
                if(foundValue->is_structured())
                {
                    // std::stringstream errorStr;
                    // errorStr << "Error Field [\"" << field << "\"] exist but the return type (nlohmann::json) is not good!" << std::endl;
                    // throw std::overflow_error(errorStr.str());
                    // std::stringstream errorStr;
                    // errorStr << "Error Field exist but the return type ("<< typeid(T).name() << ") is not good, field [\"" << field << "\"] is a structure!" << std::endl;
                    // throw std::overflow_error(errorStr.str());
                    std::cout << "Error Field exist but the return type ("<< typeid(T).name() << ") is not good, field [\"" << field << "\"] is a structure!" << std::endl;
                    return T();
                }

                try {
                    return *foundValue;
                }
                catch(const std::exception& e)
                {
                    // Propagate the exception
                    // std::cout <<"Error catch : " << e.what() << std::endl;
                    throw;
                }
            }
            std::cout << "ERROR Field doesn't exist!" << std::endl;
            return T();
        }

        template<>
            nlohmann::json SettingsManager::getSettings(nlohmann::json& json, char const* field);

        template<typename T, typename U, typename... Args>
        T SettingsManager::getSettings(nlohmann::json& json, U firstField, Args... args)
        {
            if (auto foundValue = json.find(firstField);
                isSettingsExist(json, foundValue))
            {
                if(foundValue->is_object())
                {
                    return getSettings<T>(json[firstField], args...);
                }
                return *foundValue;
            }
            std::cout << "ERROR Field doesn't exist!" << std::endl;
            return T();
        }
    } // namespace Manager
} // namespace BookManager