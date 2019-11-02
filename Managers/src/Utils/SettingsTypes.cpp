#include "Managers/Utils/SettingsTypes.hpp"
#include <iostream>

namespace BookManager
{
    namespace Manager
    {
        void to_json(nlohmann::json& j, const GeneralSettings& generalSettings)
        {
        }

        void from_json(const nlohmann::json& j, GeneralSettings& generalSettings)
        {
        }

        void to_json(nlohmann::json& j, const BookSettings& bookSetting)
        {
            j = nlohmann::json{
                    {"showCover", bookSetting.showCover},
                    {"sort", bookSetting.sort},
                    {"showPerson", bookSetting.showPerson}
                };
        }

        void from_json(const nlohmann::json& j, BookSettings& bookSetting)
        {
            std::string err;
            BookSettings defaultSetting{};
            try_catch_from_json(j, "showCover", bookSetting.showCover, defaultSetting.showCover, err);
            try_catch_from_json(j, "sort", bookSetting.sort, defaultSetting.sort, err);
            try_catch_from_json(j, "showPerson", bookSetting.showPerson, defaultSetting.showPerson, err);

            if(err.size() > 0)
            {
                throwError<BookSettings>(err);
            }
        }

        void to_json(nlohmann::json& j, const CategorySettings& categorySettings)
        {
            j = nlohmann::json{{"sort", categorySettings.sort}};
        }

        void from_json(const nlohmann::json& j, CategorySettings& categorySettings)
        {
            std::string err;
            CategorySettings defaultSetting{};
            try_catch_from_json(j, "sort", categorySettings.sort, defaultSetting.sort, err);

            if(err.size() > 0)
            {
                throwError<CategorySettings>(err);
            }
        }

        void to_json(nlohmann::json& j, const PersonSettings& personSettings)
        {
            j = nlohmann::json{
                    {"sort", personSettings.sort},
                    {"showBooks", personSettings.showBooks}
                };
        }

        void from_json(const nlohmann::json& j, PersonSettings& personSettings)
        {
            std::string err;
            PersonSettings defaultSetting{};
            try_catch_from_json(j, "sort", personSettings.sort, defaultSetting.sort, err);
            try_catch_from_json(j, "showBooks", personSettings.showBooks, defaultSetting.showBooks, err);

            if(err.size() > 0)
            {
                throwError<PersonSettings>(err);
            }
        }
    } // namespace Manager
} // namespace BookManager