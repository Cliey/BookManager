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
    // Update Publisher with Id = 4
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
    // Update Category with Id = 4
    BookManager::Category::Category updatedCategory{3, "Etranger"};
    EXPECT_TRUE(sut->updateCategory(updatedCategory));
}

TEST_F(TableUpdaterTest, testUpdateCategoryError_IdDoesntExist)
{
    // Update Category with Id = 9
    BookManager::Category::Category updatedCategory{9, "Hachette"};
    EXPECT_FALSE(sut->updateCategory(updatedCategory));
}


// Book Series
TEST_F(TableUpdaterTest, testUpdateBookSerieOnExistingBookSerie)
{
    // Update BookSerie with Id = 4
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
    std::shared_ptr<BookManager::Book::Abstraction::Book> book = std::make_shared<BookManager::Book::Artbook>();
    book->id = 1;
    book->author = {std::make_shared<BookManager::Entity::Person>(44, "Edward", "Rice", BookManager::Entity::Role::Author)};
    EXPECT_FALSE(sut->updateBook(book));
}

TEST_F(TableUpdaterTest, testUpdateBookError_ForeignKeySubCategory)
{
    std::shared_ptr<BookManager::Book::Abstraction::Book> book = std::make_shared<BookManager::Book::Artbook>();
    book->id = 1;
    book->author = {std::make_shared<BookManager::Entity::Person>(1, "Jacques", "Edouard", BookManager::Entity::Role::Author)};
    book->subCategory = {std::make_shared<BookManager::Category::Category>(55, "Not a Category")};
    EXPECT_FALSE(sut->updateBook(book));
}

TEST_F(TableUpdaterTest, testUpdateBookError_IdDoesntExist)
{
    // Update Book with Id = 9
    std::shared_ptr<BookManager::Book::Abstraction::Book> book = std::make_shared<BookManager::Book::Artbook>();
    book->id = 9;
    EXPECT_FALSE(sut->updateBook(book));
}