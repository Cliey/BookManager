#include "Managers/SettingsManager.hpp"
#include "Utils/Exceptions.hpp"
#include <gtest/gtest.h>

using namespace BookManager::Manager;

class SettingsManagerTest : public ::testing::Test
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
    SettingsManagerTest()
    {
        sut = SettingsManager::getSettingsManager();
    }

    SettingsManager* sut;
    nlohmann::json defaultSettings;
};

TEST_F(SettingsManagerTest, testGetOneSettingWithBool_DefaultSettings)
{
    EXPECT_TRUE(sut->getOneSetting<bool>("Book", "showCover"));
}

TEST_F(SettingsManagerTest, testGetOneSettingWithJsonStruct_DefaultSettings)
{
    auto expectedOutput = R"(
            {
                "sort": "name_asc",
                "showCover": true
            }
            )"_json;
    EXPECT_EQ(sut->getOneSetting<nlohmann::json>("Book"), expectedOutput);
}

TEST_F(SettingsManagerTest, testGetOneSettingWithStringOnBool_Exception_DefaultSettings)
{
    std::cout << "To modify, with Exception Handler" << std::endl;
    EXPECT_THROW(sut->getOneSetting<std::string>("Book", "showCover"), nlohmann::json::type_error);
    // try {
    //     sut->getOneSetting<std::string>("Book", "showCover");
    // }
    // catch(nlohmann::json::type_error& e)
    // {
    //     std::cout <<"error catch : " << e.what() << std::endl;
    // }
}

TEST_F(SettingsManagerTest, testGetOneSettingWithJsonObjectOnBool_Exception_DefaultSettings)
{
    std::cout << "To modify, with Exception Handler" << std::endl;
    EXPECT_THROW(sut->getOneSetting<nlohmann::json>("Book", "showCover"), Utils::Exceptions::E_TypeError);
    // try {
    //     sut->getOneSetting<nlohmann::json>("Book", "showCover");
    // }
    // catch(Utils::Exceptions::E_TypeError& e)
    // {
    //     std::cout <<"error catch : " << e.what() << std::endl;
    // }
}

TEST_F(SettingsManagerTest, testTypeTestOnFields)
{
    auto bookJson = sut->getOneSetting<nlohmann::json>("Book");
    EXPECT_TRUE(bookJson["sort"].is_string());
    EXPECT_FALSE(bookJson["sort"].is_structured());
}

TEST_F(SettingsManagerTest, testGetOneSettingWithBoolOnJsonObject_Exception_DefaultSettings)
{
    std::cout << "To modify, with Exception Handler" << std::endl;
    EXPECT_THROW(sut->getOneSetting<bool>("Book"), std::exception);
    // try {
    //     sut->getOneSetting<bool>("Book");
    // }
    // catch(std::exception& e)
    // {
    //     std::cout <<"error catch : " << e.what() << std::endl;
    // }
}