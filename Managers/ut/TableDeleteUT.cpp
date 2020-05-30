#include <gtest/gtest.h>
#include "Managers/Utils/TableDelete.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"
#include "Utils/Exceptions.hpp"

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
        std::shared_ptr<SQLite::Database> db = std::make_shared<SQLite::Database>(databasePathForTest, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db->exec("PRAGMA foreign_keys = ON");
        sut = std::make_shared<TableDelete>(db);
    }

    void testNoBypassElementAssociatedToABook(int idToDelete, std::string expectedLog, std::function<bool(std::shared_ptr<TableDelete>, int, bool)> fct)
    {
        testing::internal::CaptureStdout();

        EXPECT_THROW(fct(sut, idToDelete, false), Utils::Exceptions::EC_ForeignKeyFound);

        std::string output = testing::internal::GetCapturedStdout();
        DatabaseManagerTestCommon::checkLogOutput(output, expectedLog);
    }

    std::shared_ptr<TableDelete> sut;

};

// Person
TEST_F(TableDeleteTest, tableDeletePersonBypassForeignKey)
{
    int idToDelete{3};
    EXPECT_TRUE(sut->checkAndDeleteInPersonTable(idToDelete, true));
}

TEST_F(TableDeleteTest, tableDeletePersonNoBypass)
{
    int idToDelete{1};
    std::string expectedLog = "Warning : the author \"Edouard, Jacques\" has 2 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::checkAndDeleteInPersonTable);
}

TEST_F(TableDeleteTest, tableDeletePersonNoBypassNoBookAssociated)
{
    int idToDelete{4};
    EXPECT_TRUE(sut->checkAndDeleteInPersonTable(idToDelete, false));
}

TEST_F(TableDeleteTest, tableDeletePersonDoesntExist)
{
    int idToDelete{55};
    EXPECT_FALSE(sut->checkAndDeleteInPersonTable(idToDelete, false));
}

// Publisher
TEST_F(TableDeleteTest, tableDeletePublisherBypassForeignKey)
{
    int idToDelete{1};
    EXPECT_TRUE(sut->checkAndDeleteInPublisherTable(idToDelete, true));
}

TEST_F(TableDeleteTest, tableDeletePublisherNoBypass)
{
    int idToDelete{2};
    std::string expectedLog = "Warning : the publisher \"Mu\" has 1 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::checkAndDeleteInPublisherTable);
}

TEST_F(TableDeleteTest, tableDeletePublisherNoBypassNoBookAssociated)
{
    int idToDelete{3};
    EXPECT_TRUE(sut->checkAndDeleteInPublisherTable(idToDelete, false));
}

TEST_F(TableDeleteTest, tableDeletePublisherDoesntExist)
{
    int idToDelete{54};
    EXPECT_FALSE(sut->checkAndDeleteInPublisherTable(idToDelete, false));
}

// Category
TEST_F(TableDeleteTest, tableDeleteCategoryBypassForeignKey)
{
    int idToDelete{1};
    EXPECT_TRUE(sut->checkAndDeleteInCategoryTable(idToDelete, true));
}

TEST_F(TableDeleteTest, tableDeleteCategoryNoBypass_MainCategoryOfABook)
{
    int idToDelete{2};
    std::string expectedLog = "Warning : the category \"Sci-Fi\" has 1 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::checkAndDeleteInCategoryTable);
}

TEST_F(TableDeleteTest, tableDeleteCategoryNoBypass_MainCategoryAndSubcategoryOfBooks)
{
    int idToDelete{3};
    std::string expectedLog = "Warning : the category \"Fantasy\" has 2 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::checkAndDeleteInCategoryTable);
}

TEST_F(TableDeleteTest, tableDeleteCategoryNoBypass_SubcategoryOfABook)
{
    int idToDelete{4};
    std::string expectedLog = "Warning : the category \"Young Adult\" has 1 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::checkAndDeleteInCategoryTable);
}

TEST_F(TableDeleteTest, tableDeleteCategoryNoBypassNoBookAssociated)
{
    int idToDelete{5};
    EXPECT_TRUE(sut->checkAndDeleteInCategoryTable(idToDelete, false));
}

TEST_F(TableDeleteTest, tableDeleteCategoryDoesntExist)
{
    int idToDelete{55};
    EXPECT_FALSE(sut->checkAndDeleteInCategoryTable(idToDelete, false));
}

// Book Series
TEST_F(TableDeleteTest, tableDeleteBookSeriesBypassForeignKey)
{
    int idToDelete{3};
    EXPECT_TRUE(sut->checkAndDeleteInBookSeriesTable(idToDelete, true));
}

TEST_F(TableDeleteTest, tableDeleteBookSeriesNoBypass)
{
    int idToDelete{1};
    std::string expectedLog = "Warning : the book series \"Harry Potter\" has 1 book(s) associated, are you sure you want to delete it?";
    testNoBypassElementAssociatedToABook(idToDelete, expectedLog, &TableDelete::checkAndDeleteInBookSeriesTable);
}

TEST_F(TableDeleteTest, tableDeleteBookSeriesNoBypassNoBookAssociated)
{
    int idToDelete{2};
    EXPECT_TRUE(sut->checkAndDeleteInBookSeriesTable(idToDelete, false));
}

TEST_F(TableDeleteTest, tableDeleteBookSeriesDoesntExist)
{
    int idToDelete{44};
    EXPECT_FALSE(sut->checkAndDeleteInBookSeriesTable(idToDelete, false));
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