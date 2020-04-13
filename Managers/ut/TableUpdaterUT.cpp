#include <gtest/gtest.h>
#include "Managers/Utils/TableUpdater.hpp"
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

class TableUpdaterTest : public ::testing::Test
{
public:

    static void SetUpTestSuite()
    {
        DatabaseManagerTestCommon::initDbTest();
    }

    std::shared_ptr<BookManager::Book::Abstraction::Book> initBookTestAllOptionalField()
    {
        std::shared_ptr<BookManager::Book::Abstraction::Book> book = std::make_shared<BookManager::Book::Novel>();
        book->id = 2;
        book->title = "TestBook";
        std::vector<std::shared_ptr<BookManager::Entity::Person>> authorsVec;
        std::vector<std::shared_ptr<BookManager::Entity::Person>> authorsVector;
        std::shared_ptr<BookManager::Entity::Person> authorJacquesEdouard = initAuthor(1, "Jacques", "Edouard", BookManager::Entity::Role::Author);
        std::shared_ptr<BookManager::Entity::Person> authorPeterJackson = initAuthor(3, "Peter", "Jackson", BookManager::Entity::Role::Author);
        authorsVector.push_back(authorJacquesEdouard);
        authorsVector.push_back(authorPeterJackson);
        book->author = authorsVector;
        book->mainCategory = std::make_shared<BookManager::Category::Category>(2, "Sci-Fi");
        std::vector<std::shared_ptr<BookManager::Category::Category>>  subCategory =
            {std::make_shared<BookManager::Category::Category>(4, "Young Adult"),
            std::make_shared<BookManager::Category::Category>(3, "Fantasy")};
        book->subCategory = subCategory;
        book->publisher = std::make_shared<BookManager::Entity::Publisher>(2, "Mu");
        book->bookSerie = std::make_shared<BookManager::Entity::BookSerie>(3, "Star Wars");
        book->published = std::make_optional<std::time_t>(initDate(2018, 7, 21));
        book->purchasedDate = std::make_optional<std::time_t>(initDate(2019, 12, 4));
        book->status = BookManager::Book::BookStatus::WantIt;
        book->price = 3.7;
        book->isRead = true;
        book->startReadingDate = std::make_optional<std::time_t>(initDate(2020, 1, 4));
        book->endReadingDate = std::make_optional<std::time_t>(initDate(2020, 2, 7));
        book->rate = 8;
        return book;
    }

    std::shared_ptr<BookManager::Book::Abstraction::Book> initBookTestNoOptionalField()
    {
        std::shared_ptr<BookManager::Book::Abstraction::Book> book = std::make_shared<BookManager::Book::Artbook>();
        book->id = 1;
        book->title = "ArtBook Toy Story";
        std::vector<std::shared_ptr<BookManager::Entity::Person>> authorsVector;
        std::shared_ptr<BookManager::Entity::Person> authorJacquesEdouard = initAuthor(1, "Jacques", "Edouard", BookManager::Entity::Role::Author);
        authorsVector.push_back(authorJacquesEdouard);
        book->author = authorsVector;
        book->mainCategory = std::make_shared<BookManager::Category::Category>(1, "Thriller");
        book->publisher = std::make_shared<BookManager::Entity::Publisher>(1, "12-25");
        book->published = std::make_optional<std::time_t>(initDate(2017, 2, 4));
        book->isRead = false;
        return book;
    }

    TableUpdaterTest()
    {
        std::shared_ptr<SQLite::Database> db = std::make_shared<SQLite::Database>("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db->exec("PRAGMA foreign_keys = ON");
        sut = std::make_shared<TableUpdater>(db);
    }

    std::shared_ptr<TableUpdater> sut;

private:
    std::time_t initDate(int year, int month, int day)
    {
        std::tm date{};
        date.tm_year = year - 1900; // Year since 1900
        date.tm_mon = month - 1; // 0 tu 11
        date.tm_mday = day;
        return (std::mktime(&date));
    }

    std::shared_ptr<BookManager::Entity::Person> initAuthor(int id, std::string firstName, std::string lastName, BookManager::Entity::Role role)
    {
        return std::make_shared<BookManager::Entity::Person>(id, firstName, lastName, role);
    }

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
    auto book = initBookTestNoOptionalField();
    EXPECT_TRUE(sut->updateBook(book));
}

TEST_F(TableUpdaterTest, testUpdateBookOnExistingBookAllOptionalFieldSetted)
{
    // Update Book with Id = 2
    auto book = initBookTestAllOptionalField();
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