#pragma once
#include "Utils/Exceptions.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <nlohmann_json/json.hpp>

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
            static std::shared_ptr<SettingsManager> getSettingsManager();

            void saveSettings();
            template<typename T, typename... Args>
            T getOneSetting(char const*, Args...);
            void printSettings();

            SettingsManager(const SettingsManager&) = delete;
            SettingsManager& operator=(const SettingsManager&) = delete;
        private:
            SettingsManager();

            void loadSettings();
            void setDefaultSettings();
            template<typename T>
            T getSettings(nlohmann::json&, char const*);
            template<typename T, typename U = char const*, typename... Args>
            T getSettings(nlohmann::json&, U, Args...);

            bool isSettingsExist(std::string);
            bool isSettingsExist(nlohmann::json&, nlohmann::json::iterator&);

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
                    std::stringstream errorStr;
                    errorStr << "Error Field [\"" << field << "\"] exist but the return type ("<< typeid(T).name() << ") is not good, field [\"" << field << "\"] is a structure!";
                    throw Utils::Exceptions::E_TypeError(errorStr.str());
                }

                try {
                    return *foundValue;
                }
                catch(const std::exception& e)
                {
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

        template<typename T, typename... Args>
        T SettingsManager::getOneSetting(char const* firstField, Args... args)
        {
            return getSettings<T>(settingsJson, firstField, args...);
        }
    } // namespace Manager
} // namespace BookManager