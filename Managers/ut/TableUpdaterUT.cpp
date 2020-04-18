#include <gtest/gtest.h>
#include "Managers/Utils/TableUpdater.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"

#include "BookAbstract/Book.hpp"
#include "EntityTypes/BookSerie.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "../../Category.hpp"
#include "BookTypes/Novel.hpp"
#include "BookTypes/Artbook.hpp"

using namespace BookManager::Manager;

class TableUpdaterTest : public ::testing::Test
{
public:

    static void SetUpTestSuite()
    {
        DatabaseManagerTestCommon::initDbTest();
    }

    TableUpdaterTest()
    {
        std::shared_ptr<SQLite::Database> db = std::make_shared<SQLite::Database>("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db->exec("PRAGMA foreign_keys = ON");
        sut = std::make_shared<TableUpdater>(db);
    }

    void updateBookWithException(std::shared_ptr<BookManager::Book::Abstraction::Book> book, std::string expectedLog)
    {
        testing::internal::CaptureStdout();

        EXPECT_FALSE(sut->updateBook(book));

        std::string output = testing::internal::GetCapturedStdout();
        DatabaseManagerTestCommon::checkLogOutput(output, expectedLog);
    }

    std::shared_ptr<TableUpdater> sut;
};

// Person
TEST_F(TableUpdaterTest, testUpdatePersonOnExistingPerson)
{
    // Update Author with Id = 4
    BookManager::Entity::Person updatedAuthor {4, "John", "McCain", BookManager::Entity::Role::Author};
    EXPECT_TRUE(sut->updatePerson(updatedAuthor));
}

TEST_F(TableUpdaterTest, testUpdatePersonError_IdDoesntExist)
{
    // Update Author with Id = 9
    BookManager::Entity::Person updatedAuthor {9, "John", "McCain", BookManager::Entity::Role::Author};
    EXPECT_FALSE(sut->updatePerson(updatedAuthor));
}

// Publisher
TEST_F(TableUpdaterTest, testUpdatePublisherOnExistingPublisher)
{
    // Update Publisher with Id = 3
    BookManager::Entity::Publisher updatedPublisher{3, "Hachette"};
    EXPECT_TRUE(sut->updatePublisher(updatedPublisher));
}

TEST_F(TableUpdaterTest, testUpdatePublisherError_IdDoesntExist)
{
    // Update Publisher with Id = 9
    BookManager::Entity::Publisher updatedPublisher{9, "Hachette"};
    EXPECT_FALSE(sut->updatePublisher(updatedPublisher));
}

// Category
TEST_F(TableUpdaterTest, testUpdateCategoryOnExistingCategory)
{
    // Update Category with Id = 3
    BookManager::Category::Category updatedCategory{3, "Etranger"};
    EXPECT_TRUE(sut->updateCategory(updatedCategory));
}

TEST_F(TableUpdaterTest, testUpdateCategoryError_IdDoesntExist)
{
    // Update Category with Id = 44
    BookManager::Category::Category updatedCategory{44, "Hachette"};
    EXPECT_FALSE(sut->updateCategory(updatedCategory));
}


// Book Series
TEST_F(TableUpdaterTest, testUpdateBookSerieOnExistingBookSerie)
{
    // Update BookSerie with Id = 3
    BookManager::Entity::BookSerie updatedBookSerie{3, "Cycle de l'epee"};
    EXPECT_TRUE(sut->updateBookSerie(updatedBookSerie));
}

TEST_F(TableUpdaterTest, testUpdateBookSerieError_IdDoesntExist)
{
    // Update BookSerie with Id = 9
    BookManager::Entity::BookSerie updatedBookSerie{9, "Cycle de l'epee"};
    EXPECT_FALSE(sut->updateBookSerie(updatedBookSerie));
}

// Book
TEST_F(TableUpdaterTest, testUpdateBookOnExistingBookNoOptionalFieldSetted)
{
    // Update Book with Id = 1
    auto book = DatabaseManagerTestCommon::initBookTestNoOptionalField();
    EXPECT_TRUE(sut->updateBook(book));
}

TEST_F(TableUpdaterTest, testUpdateBookOnExistingBookAllOptionalFieldSetted)
{
    // Update Book with Id = 2
    auto book = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    EXPECT_TRUE(sut->updateBook(book));
}

TEST_F(TableUpdaterTest, testUpdateBookError_ForeignKeyAuthor)
{
    auto book = DatabaseManagerTestCommon::initBookTestNoOptionalField();
    book->author = {std::make_shared<BookManager::Entity::Person>(44, "Edward", "Rice", BookManager::Entity::Role::Author)};

    std::string expectedLog = "Error occured with author : The author \"Rice, Edward\" doesn't exist";
    updateBookWithException(book, expectedLog);
}

TEST_F(TableUpdaterTest, testUpdateBookError_ForeignKeySubCategory)
{
    auto book = DatabaseManagerTestCommon::initBookTestNoOptionalField();
    book->subCategory = {std::make_shared<BookManager::Category::Category>(55, "Not a Category")};

    std::string expectedLog = "Error occured with Subcategories : The Subcategory \"Not a category\" doesn't exist.";
    updateBookWithException(book, expectedLog);
}

TEST_F(TableUpdaterTest, testUpdateBookError_IdDoesntExist)
{
    // Update Book with Id = 980
    auto book = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    book->id = 980;
    std::string expectedLog = "Error occured while updating Book : Id is not associated to any book";
    updateBookWithException(book, expectedLog);
}