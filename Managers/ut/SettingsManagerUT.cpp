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

    std::shared_ptr<SettingsManager> sut;
    nlohmann::json defaultSettings;
};

TEST_F(SettingsManagerTest, testGetValueOneSettingWithBool_DefaultSettings)
{
    EXPECT_TRUE(sut->getValueOneSetting<bool>("Book", "showCover"));
}

TEST_F(SettingsManagerTest, testGetValueOneSettingWithJsonStruct_DefaultSettings)
{
    auto expectedOutput = R"(
            {
                "sort": "name_asc",
                "showCover": true
            }
            )"_json;
    EXPECT_EQ(sut->getValueOneSetting<nlohmann::json>("Book"), expectedOutput);
}

TEST_F(SettingsManagerTest, testGetValueOneSettingWithStringOnBool_Exception_DefaultSettings)
{
    EXPECT_THROW(sut->getValueOneSetting<std::string>("Book", "showCover"), nlohmann::json::type_error);
    try {
        sut->getValueOneSetting<std::string>("Book", "showCover");
    }
    catch(nlohmann::json::type_error& e)
    {
        std::cout <<"error catch : " << e.what() << std::endl;
    }
}

TEST_F(SettingsManagerTest, testGetValueOneSettingWithJsonObjectOnBool_Exception_DefaultSettings)
{
    EXPECT_THROW(sut->getValueOneSetting<nlohmann::json>("Book", "showCover"), Utils::Exceptions::E_TypeError);
    try {
        auto out = sut->getValueOneSetting<nlohmann::json>("Book", "showCover");
        std::cout << "out = " << out.is_object();
    }
    catch(Utils::Exceptions::E_TypeError& e)
    {
        std::cout <<"error catch : " << e.what() << std::endl;
    }
}

TEST_F(SettingsManagerTest, testTypeTestOnFields)
{
    auto bookJson = sut->getValueOneSetting<nlohmann::json>("Book");
    EXPECT_TRUE(bookJson["sort"].is_string());
    EXPECT_FALSE(bookJson["sort"].is_structured());
}

TEST_F(SettingsManagerTest, testGetValueOneSettingWithBoolOnJsonObject_Exception_DefaultSettings)
{
    EXPECT_THROW(sut->getValueOneSetting<bool>("Book"), Utils::Exceptions::E_TypeError);
    try {
        sut->getValueOneSetting<bool>("Book");
    }
    catch(std::exception& e)
    {
        std::cout <<"error catch : " << e.what() << std::endl;
    }
}

TEST_F(SettingsManagerTest, testGetValueOneSetting_FieldDoesntExist_FirstLayer)
{
    EXPECT_THROW(sut->getValueOneSetting<bool>("Cat", "dog"), Utils::Exceptions::E_FieldNotFound);
    try {
        sut->getValueOneSetting<bool>("Cat", "dog");
    }
    catch(Utils::Exceptions::E_FieldNotFound& e)
    {
        std::cout <<"error catch : " << e.what() << std::endl;
    }
}

TEST_F(SettingsManagerTest, testGetValueOneSetting_FieldDoesntExist_SecondLayer)
{
    EXPECT_THROW(sut->getValueOneSetting<bool>("Book", "dog"), Utils::Exceptions::E_FieldNotFound);
    try {
        sut->getValueOneSetting<bool>("Book", "dog");
    }
    catch(Utils::Exceptions::E_FieldNotFound& e)
    {
        std::cout <<"error catch : " << e.what() << std::endl;
    }
}

TEST_F(SettingsManagerTest, testGetValueOneSetting_FieldDoesntExist_Json)
{
    EXPECT_THROW(sut->getValueOneSetting<nlohmann::json>("Child"), Utils::Exceptions::E_FieldNotFound);
    try {
        sut->getValueOneSetting<nlohmann::json>("Child");
    }
    catch(Utils::Exceptions::E_FieldNotFound& e)
    {
        std::cout <<"error catch : " << e.what() << std::endl;
    }
}

TEST_F(SettingsManagerTest, testGetValue_ChangeValue)
{
    EXPECT_TRUE(sut->getValueOneSetting<bool>("Book", "showCover"));
    sut->setSettingTo<bool>(false, "Book", "showCover");
    EXPECT_FALSE(sut->getValueOneSetting<bool>("Book", "showCover"));
}