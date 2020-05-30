#include <gtest/gtest.h>
#include "Managers/Utils/TableInsert.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"

#include "BookAbstract/Book.hpp"
#include "EntityTypes/BookSerie.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "../../Category.hpp"
#include "MaillonCreation/BookCreationResponsibility.hpp"
#include "MaillonCreation/MaillonCreationBookArtBook.hpp"
#include "MaillonCreation/MaillonCreationBookNovel.hpp"
#include "MaillonCreation/MaillonCreationBookComics.hpp"
#include "MaillonCreation/MaillonCreationBookManga.hpp"
#include "BookFactory/BookFactory.hpp"

using namespace BookManager::Manager;

class TableInsertTest : public ::testing::Test
{
public:

    static void SetUpTestSuite()
    {
        DatabaseManagerTestCommon::initDbTest();
    }

    TableInsertTest()
    {
        std::shared_ptr<SQLite::Database> db = std::make_shared<SQLite::Database>(databasePathForTest, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db->exec("PRAGMA foreign_keys = ON");
        sut = std::make_shared<TableInsert>(db);
    }

    void addBookWithException(std::shared_ptr<BookManager::Book::Abstraction::Book> book, std::string expectedLog)
    {
        testing::internal::CaptureStdout();

        EXPECT_FALSE(sut->addBook(book));

        std::string output = testing::internal::GetCapturedStdout();
        DatabaseManagerTestCommon::checkLogOutput(output, expectedLog);
    }

    std::shared_ptr<TableInsert> sut;

};

// Person
TEST_F(TableInsertTest, testInsertPerson)
{
    // Add Author with Id = 6, id doesn't matter
    BookManager::Entity::Person newAuthor {6, "Edward", "Rice", BookManager::Entity::Role::Author};
    EXPECT_TRUE(sut->addPerson(newAuthor));
}

// Publisher
TEST_F(TableInsertTest, testInsertPublisher)
{
    // Add Publisher with Id = 55, id doesn't matter
    BookManager::Entity::Publisher newPublisher{55, "Hachette"};
    EXPECT_TRUE(sut->addPublisher(newPublisher));
}

// Category
TEST_F(TableInsertTest, testInsertCategory)
{
    // Add Category with Id = 65, id doesn't matter
    BookManager::Category::Category newCategory{65, "Etranger"};
    EXPECT_TRUE(sut->addCategory(newCategory));
}


// Book Series
TEST_F(TableInsertTest, testInsertBookSerie)
{
    // Add BookSerie with Id = 65, id doesn't matter
    BookManager::Entity::BookSerie newBookSerie{65, "Cycle de l'epee"};
    EXPECT_TRUE(sut->addBookSerie(newBookSerie));
}

// Book
TEST_F(TableInsertTest, testInsertBookNoOptionalFieldSetted)
{
    // Update Book with Id = 1, id doesn't matter
    auto book = DatabaseManagerTestCommon::initBookTestNoOptionalField();
    EXPECT_TRUE(sut->addBook(book));
}

TEST_F(TableInsertTest, testInsertBookAllOptionalFieldSetted)
{
    // Update Book with Id = 2, id doesn't matter
    auto book = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    EXPECT_TRUE(sut->addBook(book));
}

TEST_F(TableInsertTest, testInsertBookError_ForeignKeyAuthor)
{
    auto book = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    book->generalInfo.author = {std::make_shared<BookManager::Entity::Person>(44, "Edward", "Rice", BookManager::Entity::Role::Author)};

    std::string expectedLog = "Error occured with author : The author \"Rice, Edward\" doesn't exist";
    addBookWithException(book, expectedLog);
}

TEST_F(TableInsertTest, testInsertBookError_ForeignKeySubCategory)
{
    auto book = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    book->categoryInfo.subCategory = {std::make_shared<BookManager::Category::Category>(55, "Not a Category")};

    std::string expectedLog = "Error occured with Subcategories : The Subcategory \"Not a category\" doesn't exist.";
    addBookWithException(book, expectedLog);
}