#pragma once
#include "Managers/Utils/SortingEnum.hpp"
#include "Managers/Utils/SettingsTypes.hpp"

namespace BookManager
{
    namespace Manager
    {
        enum class SettingType : uint8_t
        {
            GeneralSetting, BookSetting, CategorySetting, PersonSetting
        };

        class SettingsManager
        {
        public:
            SettingsManager(std::string filename);

            void saveSettings();

            GeneralSettings getGeneralSettings() { return this->generalSettings; }
            BookSettings getBookSettings() { return this->bookSettings; }
            CategorySettings getCategorySettings() { return this->categorySettings; }
            PersonSettings getPersonSettings() { return this->personSettings; }

            void setGeneralSettings(GeneralSettings value) { generalSettings = value; }
            void setBookSettings(BookSettings value) { bookSettings = value; }
            void setCategorySettings(CategorySettings value) { categorySettings = value; }
            void setPersonSettings(PersonSettings value) { personSettings = value; }

            SettingsManager(const SettingsManager&) = delete;
            SettingsManager& operator=(const SettingsManager&) = delete;
        private:
            void loadSettings();
            void setDefaultSettings();
            void printSetting();

            std::string filePath;
            GeneralSettings generalSettings;
            BookSettings bookSettings;
            CategorySettings categorySettings;
            PersonSettings personSettings;
        };
    } // namespace Manager
} // namespace BookManager