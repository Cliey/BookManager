#include <gtest/gtest.h>
#include "Managers/Utils/TableDelete.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"

using namespace BookManager::Manager;

class TableDeleteTest : public ::testing::Test
{
public:

    static void SetUpTestSuite()
    {
        DatabaseManagerTestCommon::initDbTest();
    }

    TableDeleteTest()
    {
        std::shared_ptr<SQLite::Database> db = std::make_shared<SQLite::Database>("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db->exec("PRAGMA foreign_keys = ON");
        sut = std::make_shared<TableDelete>(db);
    }

    void testNoBypassElementAssociatedToABook(int idToDelete, std::string expectedLog, std::function<bool(std::shared_ptr<TableDelete>, int, bool)> fct)
    {
        testing::internal::CaptureStdout();

        EXPECT_FALSE(fct(sut, idToDelete, false));

        std::string output = testing::internal::GetCapturedStdout();
        DatabaseManagerTestCommon::checkLogOutput(output, expectedLog);
    }

    std::shared_ptr<TableDelete> sut;

};

// Person
TEST_F(TableDeleteTest, tableDeletePersonBypassForeignKey)
{
    int idToDelete{3};
    EXPECT_TRUE(sut->deleteInPersonTable(idToDelete, true));
}

TEST_F(TableDeleteTest, tableDeletePersonNoBypass)
{
    int idToDelete{1};
    std::string expectedLog = "Warning : the author has 2 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::deleteInPersonTable);
}

TEST_F(TableDeleteTest, tableDeletePersonNoBypassNoBookAssociated)
{
    int idToDelete{4};
    EXPECT_TRUE(sut->deleteInPersonTable(idToDelete, false));
}

TEST_F(TableDeleteTest, tableDeletePersonDoesntExist)
{
    int idToDelete{55};
    EXPECT_FALSE(sut->deleteInPersonTable(idToDelete, false));
}

// Publisher
TEST_F(TableDeleteTest, tableDeletePublisherBypassForeignKey)
{
    int idToDelete{1};
    EXPECT_TRUE(sut->deleteInPublisherTable(idToDelete, true));
}

TEST_F(TableDeleteTest, tableDeletePublisherNoBypass)
{
    int idToDelete{2};
    std::string expectedLog = "Warning : the publisher has 1 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::deleteInPublisherTable);
}

TEST_F(TableDeleteTest, tableDeletePublisherNoBypassNoBookAssociated)
{
    int idToDelete{3};
    EXPECT_TRUE(sut->deleteInPublisherTable(idToDelete, false));
}

TEST_F(TableDeleteTest, tableDeletePublisherDoesntExist)
{
    int idToDelete{54};
    EXPECT_FALSE(sut->deleteInPublisherTable(idToDelete, false));
}

// Category
TEST_F(TableDeleteTest, tableDeleteCategoryBypassForeignKey)
{
    int idToDelete{1};
    EXPECT_TRUE(sut->deleteInCategoryTable(idToDelete, true));
}

TEST_F(TableDeleteTest, tableDeleteCategoryNoBypass_MainCategoryOfABook)
{
    int idToDelete{2};
    std::string expectedLog = "Warning : the category has 1 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::deleteInCategoryTable);
}

TEST_F(TableDeleteTest, tableDeleteCategoryNoBypass_MainCategoryAndSubcategoryOfBooks)
{
    int idToDelete{3};
    std::string expectedLog = "Warning : the category has 2 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::deleteInCategoryTable);
}

TEST_F(TableDeleteTest, tableDeleteCategoryNoBypass_SubcategoryOfABook)
{
    int idToDelete{4};
    std::string expectedLog = "Warning : the category has 1 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::deleteInCategoryTable);
}

TEST_F(TableDeleteTest, tableDeleteCategoryNoBypassNoBookAssociated)
{
    int idToDelete{5};
    EXPECT_TRUE(sut->deleteInCategoryTable(idToDelete, false));
}

TEST_F(TableDeleteTest, tableDeleteCategoryDoesntExist)
{
    int idToDelete{55};
    EXPECT_FALSE(sut->deleteInCategoryTable(idToDelete, false));
}

// Book Serie
TEST_F(TableDeleteTest, tableDeleteBookSerieBypassForeignKey)
{
    int idToDelete{3};
    EXPECT_TRUE(sut->deleteInBookSerieTable(idToDelete, true));
}

TEST_F(TableDeleteTest, tableDeleteBookSerieNoBypass)
{
    int idToDelete{1};
    std::string expectedLog = "Warning : the book serie has 1 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::deleteInBookSerieTable);
}

TEST_F(TableDeleteTest, tableDeleteBookSerieNoBypassNoBookAssociated)
{
    int idToDelete{2};
    EXPECT_TRUE(sut->deleteInBookSerieTable(idToDelete, false));
}

TEST_F(TableDeleteTest, tableDeleteBookSerieDoesntExist)
{
    int idToDelete{44};
    EXPECT_FALSE(sut->deleteInBookSerieTable(idToDelete, false));
}

// Book
TEST_F(TableDeleteTest, tableDeleteBook)
{
    int idToDelete{1}; // No Optional field set, better to delete this
    EXPECT_TRUE(sut->deleteInBooksTable(idToDelete));
}

TEST_F(TableDeleteTest, tableDeleteBookDoesntExist)
{
    int idToDelete{44};
    EXPECT_FALSE(sut->deleteInBooksTable(idToDelete));
}