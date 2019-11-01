#include "Managers/Utils/SettingsTypes.hpp"

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
            j = nlohmann::json{{"showCover", bookSetting.showCover}, {"sort", bookSetting.sort}};
        }

        void from_json(const nlohmann::json& j, BookSettings& bookSetting)
        {
            j.at("showCover").get_to(bookSetting.showCover);
            j.at("sort").get_to(bookSetting.sort);
        }

        void to_json(nlohmann::json& j, const CategorySettings& categorySettings)
        {
            j = nlohmann::json{{"sort", categorySettings.sort}};
        }

        void from_json(const nlohmann::json& j, CategorySettings& categorySettings)
        {
            j.at("sort").get_to(categorySettings.sort);
        }

        void to_json(nlohmann::json& j, const PersonSettings& personSettings)
        {
            j = nlohmann::json{{"sort", personSettings.sort}};
        }

        void from_json(const nlohmann::json& j, PersonSettings& personSettings)
        {
            j.at("sort").get_to(personSettings.sort);
        }
    } // namespace Manager
} // namespace BookManager