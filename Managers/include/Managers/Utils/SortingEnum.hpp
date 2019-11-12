#pragma once
#include <nlohmann/json.hpp>

namespace BookManager
{
    namespace Manager
    {
        namespace Enum
        {
            enum class SortingEnumBook : uint8_t
            {
                authorName_desc, authorName_asc,
                price_desc, price_asc,
                title_desc, title_asc,
                dateAdded_desc, dateAdded_asc,
                datePublished_desc, datePublished_asc,
                undefined
            };

            NLOHMANN_JSON_SERIALIZE_ENUM( SortingEnumBook, {
                {SortingEnumBook::undefined, nullptr},
                {SortingEnumBook::authorName_desc, "authorName_desc"},
                {SortingEnumBook::authorName_asc, "authorName_asc"},
                {SortingEnumBook::price_desc, "price_desc"},
                {SortingEnumBook::price_asc, "price_asc"},
                {SortingEnumBook::title_desc, "title_desc"},
                {SortingEnumBook::title_asc, "title_asc"},
                {SortingEnumBook::dateAdded_desc, "dateAdded_desc"},
                {SortingEnumBook::dateAdded_asc, "dateAdded_asc"},
                {SortingEnumBook::datePublished_desc, "datePublished_desc"},
                {SortingEnumBook::datePublished_asc, "datePublished_asc"},
            })


            enum class SortingEnumCategory : uint8_t
            {
                name_desc, name_asc, undefined
            };

            NLOHMANN_JSON_SERIALIZE_ENUM( SortingEnumCategory, {
                {SortingEnumCategory::undefined, nullptr},
                {SortingEnumCategory::name_desc, "name_desc"},
                {SortingEnumCategory::name_asc, "name_asc"},
            })

            enum class SortingEnumPerson : uint8_t
            {
                name_desc, name_asc,
                numberBook_desc, numberBook_asc,
                undefined
            };

            NLOHMANN_JSON_SERIALIZE_ENUM( SortingEnumPerson, {
                {SortingEnumPerson::undefined, nullptr},
                {SortingEnumPerson::name_desc, "name_desc"},
                {SortingEnumPerson::name_asc, "name_asc"},
                {SortingEnumPerson::numberBook_desc, "numberBook_desc"},
                {SortingEnumPerson::numberBook_asc, "numberBook_asc"},
            })
        } // namespace Enum
    } // namespace Manager
} // namespace BookManager
