#include "Managers/SettingsManager.hpp"
#include "Utils/EnumUtils.hpp"
#include "Utils/Exceptions.hpp"
#include <gtest/gtest.h>

using namespace BookManager::Manager;

class NewSettingsManagerTest : public ::testing::Test
{
    /* Default settings : 
        "Book": {
            "sort": "name_asc",
            "showCover": true
        },
        "Person": {
            "sort": "name_desc"
        },
        "Category": {
            "sort": "name_desc"
        }
    */

   /*
   auto defaultSettings = R"(
            {
                "Book": {
                    "sort": "name_asc",
                    "showCover": true
                },
                "Person": {
                    "sort": "name_desc"
                },
                "Category": {
                    "sort": "name_desc"
                }
            }
            )"_json;
            file << std::se
            */
public:
    NewSettingsManagerTest()
    {
        sut = SettingsManager::getSettingsManager();
    }

    std::shared_ptr<SettingsManager> sut;
    nlohmann::json defaultSettings;
};

TEST_F(NewSettingsManagerTest, testDefaultValue)
{
    EXPECT_TRUE(sut->getBookSettings().showCover);
    EXPECT_EQ(sut->getBookSettings().sort, Enum::SortingEnumBook::title_asc);
    EXPECT_EQ(sut->getCategorySettings().sort, Enum::SortingEnumCategory::name_asc);
    EXPECT_EQ(sut->getPersonSettings().sort, Enum::SortingEnumPerson::name_asc);
}

TEST_F(NewSettingsManagerTest, testSetNewValue)
{
    BookSettings newValueBookSetting{false, Enum::SortingEnumBook::dateAdded_desc};
    sut->setBookSettings(newValueBookSetting);
    EXPECT_FALSE(sut->getBookSettings().showCover);
    EXPECT_EQ(sut->getBookSettings().sort, Enum::SortingEnumBook::dateAdded_desc);

    CategorySettings newValueCategorySetting{Enum::SortingEnumCategory::name_desc};
    sut->setCategorySettings(newValueCategorySetting);
    EXPECT_EQ(sut->getCategorySettings().sort, Enum::SortingEnumCategory::name_desc);

    PersonSettings newValuePersonSetting{Enum::SortingEnumPerson::name_desc};
    sut->setPersonSettings(newValuePersonSetting);
    EXPECT_EQ(sut->getPersonSettings().sort, Enum::SortingEnumPerson::name_desc);
}
