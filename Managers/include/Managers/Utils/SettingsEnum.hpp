#pragma once
#include <nlohmann/json.hpp>

namespace BookManager
{
    namespace Manager
    {
        namespace Enum
        {
            enum class DisplayBookEnum : uint8_t
            {
                listView, bookshelfView, coverView,
                undefined
            };

            NLOHMANN_JSON_SERIALIZE_ENUM( DisplayBookEnum, {
                {DisplayBookEnum::undefined, nullptr},
                {DisplayBookEnum::listView, "listView"},
                {DisplayBookEnum::bookshelfView, "bookshelfView"},
                {DisplayBookEnum::coverView, "coverView"},
            })
        } // namespace Enum
    } // namespace Manager
} // namespace BookManager