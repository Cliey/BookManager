#include "Managers/SettingsManager.hpp"
#include "Utils/EnumUtils.hpp"
#include "Utils/Exceptions.hpp"
#include <gtest/gtest.h>
#include <cstring>

using namespace BookManager::Manager;

class SettingsManagerTest : public ::testing::Test
{
    /* Default settings :
        "Book": {
            "showCover": true,
            "showPerson": false,
            "sort": "title_asc"
        },
        "Category": {
            "sort": "name_asc"
        },
        "General": {
            "objectsPerPage": 20
        },
        "Person": {
            "showBooks": false,
            "sort": "name_asc"
        }
    */

   /*
   auto defaultSettings = R"(
            {
                "Book": {
                    "showCover": true,
                    "showPerson": false,
                    "sort": "title_asc"
                },
                "Category": {
                    "sort": "name_asc"
                },
                "General": {
                    "objectsPerPage": 20
                },
                "Person": {
                    "showBooks": false,
                    "sort": "name_asc"
                }
            }
            )"_json;
            file << std::se
            */
public:
    SettingsManagerTest()
    {
        sut = SettingsManager::getSettingsManager();
    }
    std::string getLogMessage(std::string logOutput)
    {
        return (strrchr(logOutput.c_str(), '-') + 2);
    }

    std::shared_ptr<SettingsManager> sut;
    nlohmann::json defaultSettings;
};

TEST_F(SettingsManagerTest, testDefaultValue)
{
    EXPECT_TRUE(sut->getBookSettings().showCover);
    EXPECT_FALSE(sut->getBookSettings().showPerson);
    EXPECT_EQ(sut->getBookSettings().sort, Enum::SortingEnumBook::title_asc);

    EXPECT_EQ(sut->getCategorySettings().sort, Enum::SortingEnumCategory::name_asc);

    EXPECT_EQ(sut->getPersonSettings().sort, Enum::SortingEnumPerson::name_asc);
    EXPECT_FALSE(sut->getPersonSettings().showBooks);

    EXPECT_EQ(sut->getGeneralSettings().objectsPerPage, 20);
}

TEST_F(SettingsManagerTest, testSetNewValue)
{
    BookSettings newValueBookSetting{false, Enum::SortingEnumBook::dateAdded_desc, true};
    sut->setBookSettings(newValueBookSetting);
    EXPECT_FALSE(sut->getBookSettings().showCover);
    EXPECT_EQ(sut->getBookSettings().sort, Enum::SortingEnumBook::dateAdded_desc);
    EXPECT_TRUE(sut->getBookSettings().showPerson);

    CategorySettings newValueCategorySetting{Enum::SortingEnumCategory::name_desc};
    sut->setCategorySettings(newValueCategorySetting);
    EXPECT_EQ(sut->getCategorySettings().sort, Enum::SortingEnumCategory::name_desc);

    PersonSettings newValuePersonSetting{Enum::SortingEnumPerson::name_desc, true};
    sut->setPersonSettings(newValuePersonSetting);
    EXPECT_EQ(sut->getPersonSettings().sort, Enum::SortingEnumPerson::name_desc);
    EXPECT_TRUE(sut->getPersonSettings().showBooks);


    GeneralSettings newValueGeneralSettings{30};
    sut->setGeneralSettings(newValueGeneralSettings);
    EXPECT_EQ(sut->getGeneralSettings().objectsPerPage, 30);
}


TEST_F(SettingsManagerTest, testGetError)
{
    std::string err{"showCover "};
    testing::internal::CaptureStdout();
    getError<BookSettings>(err);
    std::string output = getLogMessage(testing::internal::GetCapturedStdout());
    EXPECT_EQ("Following (1) field of Book Settings has been reset : showCover \n", output);

    err = "showCover sort ";
    testing::internal::CaptureStdout();
    getError<BookSettings>(err);
    output = getLogMessage(testing::internal::GetCapturedStdout());
    EXPECT_EQ("Following (2) fields of Book Settings have been reset : showCover sort \n", output);
}