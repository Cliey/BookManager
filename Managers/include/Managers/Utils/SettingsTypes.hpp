#pragma once
#include "SortingEnum.hpp"
#include <nlohmann_json/json.hpp>

namespace BookManager
{
    namespace Manager
    {
        struct GeneralSettings {};

            void to_json(nlohmann::json&, const GeneralSettings&);
            void from_json(const nlohmann::json&, GeneralSettings&);

        struct BookSettings
        {
            bool showCover{true};
            Enum::SortingEnumBook sort{Enum::SortingEnumBook::title_asc};
        };

            void to_json(nlohmann::json&, const BookSettings&);
            void from_json(const nlohmann::json&, BookSettings&);

        struct CategorySettings
        {
            Enum::SortingEnumCategory sort{Enum::SortingEnumCategory::name_asc};
        };

            void to_json(nlohmann::json&, const CategorySettings&);
            void from_json(const nlohmann::json&, CategorySettings&);

        struct PersonSettings
        {
            Enum::SortingEnumPerson sort{Enum::SortingEnumPerson::name_asc};
        };

            void to_json(nlohmann::json&, const PersonSettings&);
            void from_json(const nlohmann::json&, PersonSettings&);
    } // namespace Manager
} // namespace BookManager