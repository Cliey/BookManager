#include <gtest/gtest.h>
#include "Managers/Utils/TableInsert.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"

#include "BookAbstract/Book.hpp"
#include "EntityTypes/BookSeries.hpp"
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

        auto [isSuccessful, maxId] = sut->addBook(book);
        EXPECT_FALSE(isSuccessful);
        EXPECT_EQ(0, maxId);

        std::string output = testing::internal::GetCapturedStdout();
        DatabaseManagerTestCommon::checkLogOutput(output, expectedLog);
    }

    void expectSuccessfulAndMaxId(std::tuple<bool, int> insertReturn, int expectedMaxId)
    {
        auto isSuccessful = std::get<0>(insertReturn);
        auto maxId = std::get<1>(insertReturn);
        EXPECT_TRUE(isSuccessful);
        EXPECT_EQ(maxId, expectedMaxId);
    }

    std::shared_ptr<TableInsert> sut;

};

// Person
TEST_F(TableInsertTest, testInsertPerson)
{
    // Add Author with Id = 6, id doesn't matter
    BookManager::Entity::Person newAuthor {6, "Edward", "Rice", BookManager::Entity::Role::Author};
    expectSuccessfulAndMaxId(sut->addPerson(newAuthor), 5);
}

// Publisher
TEST_F(TableInsertTest, testInsertPublisher)
{
    // Add Publisher with Id = 55, id doesn't matter
    BookManager::Entity::Publisher newPublisher{55, "Hachette"};
    expectSuccessfulAndMaxId(sut->addPublisher(newPublisher), 4);
}

// Category
TEST_F(TableInsertTest, testInsertCategory)
{
    // Add Category with Id = 65, id doesn't matter
    BookManager::Category::Category newCategory{65, "Etranger"};
    expectSuccessfulAndMaxId(sut->addCategory(newCategory), 6);
}


// Book Series
TEST_F(TableInsertTest, testInsertBookSeries)
{
    // Add BookSeries with Id = 65, id doesn't matter
    BookManager::Entity::BookSeries newBookSeries{65, "Cycle de l'epee"};
    expectSuccessfulAndMaxId(sut->addBookSeries(newBookSeries), 5);
}

// Book
TEST_F(TableInsertTest, testInsertBookNoOptionalFieldSetted)
{
    // Update Book with Id = 1, id doesn't matter
    auto book = DatabaseManagerTestCommon::initBookTestNoOptionalField();
    expectSuccessfulAndMaxId(sut->addBook(book), 5);
}

TEST_F(TableInsertTest, testInsertBookAllOptionalFieldSetted)
{
    // Update Book with Id = 2, id doesn't matter
    auto book = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    expectSuccessfulAndMaxId(sut->addBook(book), 6);
}

TEST_F(TableInsertTest, testInsertBookError_ForeignKeyAuthor)
{
    auto book = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    book->generalInfo.author = {std::make_shared<BookManager::Entity::Person>(44, "Edward", "Rice", BookManager::Entity::Role::Author)};

    std::string expectedLog = "Error occurred with author : The author \"Rice, Edward\" doesn't exist";
    addBookWithException(book, expectedLog);
}

TEST_F(TableInsertTest, testInsertBookError_ForeignKeySubCategory)
{
    auto book = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    book->categoryInfo.subCategory = {std::make_shared<BookManager::Category::Category>(55, "Not a Category")};

    std::string expectedLog = "Error occurred with Subcategories : The Subcategory \"Not a category\" doesn't exist.";
    addBookWithException(book, expectedLog);
}