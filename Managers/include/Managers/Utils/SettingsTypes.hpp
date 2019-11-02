#pragma once
#include "SortingEnum.hpp"
#include <nlohmann_json/json.hpp>
#include "Utils/Exceptions.hpp"
#include "Utils/Loggers.hpp"
#include <sstream>
#include <iostream>

namespace BookManager
{
    namespace Manager
    {
        struct GeneralSettings
        {
            static const char* name() { return "General Settings"; }
        };

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
        void try_catch_from_json(const nlohmann::json& j, const char* field, T& settingField, const T& defaultValue, std::string& err)
        {
            try {
                j.at(field).get_to(settingField);
            }
            catch(const std::exception& e)
            {
                err += std::string(field) + ' ';
                std::stringstream errorStr;
                errorStr << e.what() << " - Field \"" << field << "\" has been reset. t = " << typeid(T).name(); // Log_Error
                std::cout << errorStr.str() << std::endl;
                settingField = defaultValue;
            }
        }
        template <typename T>
        void throwError(std::string err) // To rename "getError"
        {
            int count = 0;
            for(int i=0; i < err.size(); i++)
            {
                if(err[i] == ' ') count++;
            }
            std::stringstream errorStr;
            errorStr << "Following (" << count << ") Fields of " << T::name() << " have been reset : " << err ; // Pop Up when loading setting
            std::cout << errorStr.str() << std::endl;
        }
    } // namespace Manager
} // namespace BookManager