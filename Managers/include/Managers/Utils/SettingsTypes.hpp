#pragma once
#include <algorithm>
#include <nlohmann/json.hpp>
#include "SortingEnum.hpp"
#include "Utils/Log.hpp"

#define AUTHORIZED_OBJECT_PER_PAGE std::vector<unsigned char>{20, 50, 100}

namespace BookManager
{
    namespace Manager
    {
        struct GeneralSettings
        {
            unsigned char objectsPerPage{20}; // Can take value 20, 50 or 100
            static const char* name() { return "General Settings"; }
        };
            template<typename T>
            bool verifyT(std::vector<T> authorizedValue, T objectToCheck)
            {
                 if(std::find(authorizedValue.begin(), authorizedValue.end(), objectToCheck) == authorizedValue.end())
                {
                    return false;
                }
                return true;
            }

            void to_json(nlohmann::json&, const GeneralSettings&);
            void from_json(const nlohmann::json&, GeneralSettings&);

        struct BookSettings
        {
            bool showCover{true};
            Enum::SortingEnumBook sort{Enum::SortingEnumBook::title_asc};
            bool showPerson{false};
            static const char* name() { return "Book Settings"; }
        };

            void to_json(nlohmann::json&, const BookSettings&);
            void from_json(const nlohmann::json&, BookSettings&);

        struct CategorySettings
        {
            Enum::SortingEnumCategory sort{Enum::SortingEnumCategory::name_asc};
            static const char* name() { return "Category Settings"; }
        };

            void to_json(nlohmann::json&, const CategorySettings&);
            void from_json(const nlohmann::json&, CategorySettings&);

        struct PersonSettings
        {
            Enum::SortingEnumPerson sort{Enum::SortingEnumPerson::name_asc};
            bool showBooks{false};
            static const char* name() { return "Person Settings"; }
        };

            void to_json(nlohmann::json&, const PersonSettings&);
            void from_json(const nlohmann::json&, PersonSettings&);


        template <typename T>
        bool try_catch_from_json(const nlohmann::json& j, const char* field, T& settingField, const T& defaultValue, std::string& err)
        {
            /* Return true if an error is catch */
            try {
                j.at(field).get_to(settingField);
            }
            catch(const std::exception& e)
            {
                err += std::string(field) + ' ';
                settingField = defaultValue;
                LOG_ERROR("{} - Field \"{}\" has been reset.", e.what(), field);
                return true;
            }
            return false;
        }

        template <typename T>
        void try_catch_from_json_withRangedParam(const nlohmann::json& j, const char* field, T& settingField, const T& defaultValue, std::vector<T> authorizedValue, std::string& err)
        {
            if(try_catch_from_json(j, field, settingField, defaultValue, err))
                return;

            if(!verifyT(authorizedValue, settingField))
            {
                err += std::string(field) + ' ';
                LOG_WINDOW("The value {} for \"{}\" is not authorized, the value will be set at it's default value ({})", settingField, field, defaultValue);
                settingField = defaultValue;
            }
        }

        template <typename T>
        void getError(std::string err)
        {
            int count = count_if(err.begin(), err.end(), [](char c){ return c == ' '; });
            if(count > 1)
            {
                LOG_WINDOW("Following ({}) fields of {} have been reset : {}", count, T::name(), err.c_str());
            }
            else
            {
                LOG_WINDOW("Following ({}) field of {} has been reset : {}", count, T::name(), err.c_str());
            }
        }
    } // namespace Manager
} // namespace BookManager