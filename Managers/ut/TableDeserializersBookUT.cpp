#include "TableDeserializersUT_Common.hpp"
#include "Utils/TestUtils.hpp"

#include "MaillonCreation/BookCreationResponsibility.hpp"
#include "MaillonCreation/MaillonCreationBookArtBook.hpp"
#include "MaillonCreation/MaillonCreationBookNovel.hpp"
#include "MaillonCreation/MaillonCreationBookComics.hpp"
#include "MaillonCreation/MaillonCreationBookManga.hpp"
#include "BookFactory/BookFactory.hpp"

using namespace BookManager::Manager;
using namespace BookManager::Book;

class TableDeserializersBookTest : public TableDeserializersCommon
{
public:
    void initBookFactoryMaillon()
    {
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookArtBook>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookNovel>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookComics>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookManga>());
    }

    std::shared_ptr<BookManager::Book::Abstraction::Book> initBookTest2()
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

    std::shared_ptr<BookManager::Book::Abstraction::Book> initBookTest1()
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

    void expectBookTable(std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable, std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            EXPECT_EQ(deserializedTable[i]->getType(), expectedDeserializedTable[i]->getType());
            EXPECT_EQ(deserializedTable[i]->id, expectedDeserializedTable[i]->id);
            EXPECT_EQ(deserializedTable[i]->title, expectedDeserializedTable[i]->title);
            expectPersonTable(deserializedTable[i]->author, expectedDeserializedTable[i]->author);
            expectOneIdAndName<BookManager::Category::Category>(deserializedTable[i]->mainCategory, expectedDeserializedTable[i]->mainCategory);
            expectIdAndName<BookManager::Category::Category>(deserializedTable[i]->subCategory, expectedDeserializedTable[i]->subCategory);
            expectOneIdAndName<BookManager::Entity::Publisher>(deserializedTable[i]->publisher, expectedDeserializedTable[i]->publisher);
            expectOneIdAndName<BookManager::Entity::BookSerie>(deserializedTable[i]->bookSerie, expectedDeserializedTable[i]->bookSerie);

            CheckOptionalField::check<std::time_t>(deserializedTable[i]->published, expectedDeserializedTable[i]->published);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->purchasedDate, expectedDeserializedTable[i]->purchasedDate);
            CheckOptionalField::check<double>(deserializedTable[i]->price, expectedDeserializedTable[i]->price);
            EXPECT_EQ(deserializedTable[i]->status, expectedDeserializedTable[i]->status);
            EXPECT_EQ(deserializedTable[i]->isRead, expectedDeserializedTable[i]->isRead);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->startReadingDate, expectedDeserializedTable[i]->startReadingDate);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->endReadingDate, expectedDeserializedTable[i]->endReadingDate);
            EXPECT_EQ(deserializedTable[i]->rate, expectedDeserializedTable[i]->rate);
        }
    }

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

TEST_F(TableDeserializersBookTest, testGetBookVectorNoOffset)
{
    initBookFactoryMaillon();
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable{};

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTest1 = initBookTest1();
    expectedDeserializedTable.push_back(bookTest1);

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTest2 = initBookTest2();
    expectedDeserializedTable.push_back(bookTest2);

    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable;
    deserializedTable = sut->deserializeBookTable(4, 0);
    expectBookTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersBookTest, testGetBookVectorWithOffset)
{
    initBookFactoryMaillon();
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable{};

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTest = initBookTest2();
    expectedDeserializedTable.push_back(bookTest);

    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable;
    deserializedTable = sut->deserializeBookTable(2, 1);
    expectBookTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersBookTest, testGetBookVectorWithOffsetTooLarge)
{
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable;
    deserializedTable = sut->deserializeBookTable(3, 2000);
    EXPECT_TRUE(deserializedTable.empty());
}