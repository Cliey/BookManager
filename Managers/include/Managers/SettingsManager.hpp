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
            void printSettings();

            template<typename T, typename... Args>
                T getValueOneSetting(char const*, Args...);
            template<typename... Args>
                nlohmann::json getValueOneSetting(char const*, Args...);

            template<typename T, typename... Args>
                void setSettingTo(T, char const*, Args...);

            SettingsManager(const SettingsManager&) = delete;
            SettingsManager& operator=(const SettingsManager&) = delete;
        private:
            SettingsManager();

            void loadSettings();
            void setDefaultSettings();

            template<typename T>
                nlohmann::json::iterator getSettings(nlohmann::json&, char const*);
            template<typename T, typename U = char const*, typename... Args>
                nlohmann::json::iterator getSettings(nlohmann::json&, U, Args...);

            bool isSettingsExist(std::string);
            bool isSettingsExist(nlohmann::json&, nlohmann::json::iterator&);

            nlohmann::json settingsJson;
        };

        template<typename T>
        nlohmann::json::iterator SettingsManager::getSettings(nlohmann::json& json, char const* field)
        {
            if (auto foundValue = json.find(field);
                isSettingsExist(json, foundValue))
            {
                if(foundValue->is_object() && (typeid(T) != typeid(foundValue.value())))
                {
                    std::stringstream errorStr;
                    errorStr << "Field [\"" << field << "\"] exist but the return type ("<< typeid(T).name() << ") is not good, field [\"" << field << "\"] is a structure!";
                    throw Utils::Exceptions::E_TypeError(errorStr.str());
                }

                try {
                    return foundValue;
                }
                catch(const nlohmann::json::exception& e)
                {
                    throw;
                }
            }
            std::stringstream errorStr;
            errorStr << "Field [\"" << field << "\"] doesn't exist!";
            throw Utils::Exceptions::E_FieldNotFound(errorStr.str());
        }

        template<typename T, typename U, typename... Args>
        nlohmann::json::iterator SettingsManager::getSettings(nlohmann::json& json, U firstField, Args... args)
        {
            if (auto foundValue = json.find(firstField);
                isSettingsExist(json, foundValue))
            {
                if(foundValue->is_object())
                {
                    return getSettings<T>(json[firstField], args...);
                }
                return foundValue;
            }
            std::stringstream errorStr;
            errorStr << "Field [\"" << firstField << "\"] doesn't exist!";
            throw Utils::Exceptions::E_FieldNotFound(errorStr.str());
        }

        template<typename T, typename... Args>
        T SettingsManager::getValueOneSetting(char const* firstField, Args... args)
        {
            try
            {
                auto desiredSetting = getSettings<T>(settingsJson, firstField, args...);
                return desiredSetting.value();
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }

        template<typename T, typename... Args>
            void SettingsManager::setSettingTo(T newValue, char const* firstField, Args... args)
        {
            try
            {
                auto settingtoModify = getSettings<T>(settingsJson, firstField, args...);
                *settingtoModify = newValue;
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    } // namespace Manager
} // namespace BookManager