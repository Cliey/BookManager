#include <gtest/gtest.h>
#include "Managers/DatabaseManager.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"
#include "Utils/TableDeserializerUtils.hpp"
#include "Utils/TestUtils.hpp"

#include "Managers/Utils/SqlOperator/InterfaceOperator.hpp"
#include "Managers/Utils/SqlOperator/MacroSqlOperator.hpp"

#include "MaillonCreation/BookCreationResponsibility.hpp"
#include "MaillonCreation/MaillonCreationBookArtBook.hpp"
#include "MaillonCreation/MaillonCreationBookNovel.hpp"
#include "MaillonCreation/MaillonCreationBookComics.hpp"
#include "MaillonCreation/MaillonCreationBookManga.hpp"
#include "BookFactory/BookFactory.hpp"

using namespace BookManager::Manager;
using namespace BookManager::Book;

class DatabaseManagerTest : public TableDeserializerUtils
{
public:

    // static void SetUpTestSuite()
    // {
    //     // DatabaseManagerTestCommon::initDbTest();
    // }

    DatabaseManagerTest()
    {
        std::shared_ptr<SQLite::Database> db = std::make_shared<SQLite::Database>(databasePathForTest, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db->exec("PRAGMA foreign_keys = ON");
        sut = std::make_shared<DatabaseManager>(databaseNameForTest);
    }

    void initBookFactoryMaillon()
    {
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookArtBook>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookNovel>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookComics>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookManga>());
    }

    void expectBookTable(std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable, std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable)
    {
        ASSERT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            std::cout << " i = " << i << std::endl;
            EXPECT_EQ(deserializedTable[i]->getType(), expectedDeserializedTable[i]->getType());
            EXPECT_EQ(deserializedTable[i]->id, expectedDeserializedTable[i]->id);
            EXPECT_EQ(deserializedTable[i]->generalInfo.title, expectedDeserializedTable[i]->generalInfo.title);
            expectPersonTable(deserializedTable[i]->generalInfo.author, expectedDeserializedTable[i]->generalInfo.author);
            expectOneIdAndName<BookManager::Entity::Publisher>(deserializedTable[i]->generalInfo.publisher, expectedDeserializedTable[i]->generalInfo.publisher);
            expectOneIdAndName<BookManager::Entity::BookSeries>(deserializedTable[i]->generalInfo.bookSeries, expectedDeserializedTable[i]->generalInfo.bookSeries);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->generalInfo.published, expectedDeserializedTable[i]->generalInfo.published);
            expectOneIdAndName<BookManager::Category::Category>(deserializedTable[i]->categoryInfo.mainCategory, expectedDeserializedTable[i]->categoryInfo.mainCategory);
            expectIdAndName<BookManager::Category::Category>(deserializedTable[i]->categoryInfo.subCategory, expectedDeserializedTable[i]->categoryInfo.subCategory);

            CheckOptionalField::check<std::time_t>(deserializedTable[i]->statInfo.purchasedDate, expectedDeserializedTable[i]->statInfo.purchasedDate);
            CheckOptionalField::check<double>(deserializedTable[i]->statInfo.price, expectedDeserializedTable[i]->statInfo.price);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->statInfo.startReadingDate, expectedDeserializedTable[i]->statInfo.startReadingDate);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->statInfo.endReadingDate, expectedDeserializedTable[i]->statInfo.endReadingDate);
            EXPECT_EQ(deserializedTable[i]->additionalInfo.isRead, expectedDeserializedTable[i]->additionalInfo.isRead);
            EXPECT_EQ(deserializedTable[i]->additionalInfo.status, expectedDeserializedTable[i]->additionalInfo.status);
            CheckOptionalField::check<int>(deserializedTable[i]->additionalInfo.rate, expectedDeserializedTable[i]->additionalInfo.rate);
            EXPECT_EQ(deserializedTable[i]->additionalInfo.comment, expectedDeserializedTable[i]->additionalInfo.comment);
        }
    }

    std::shared_ptr<DatabaseManager> sut;
};

TEST_F(DatabaseManagerTest, testSearchPerson)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    DatabaseManager::SearchOption searchOption = {"Persons", nullptr, 10, 0, "first_name"};
    std::vector<BookManager::Entity::Person> deserializedTable = sut->searchPerson(searchOption);

    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testSearchPersonWhere_FirstNameOR)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author}};

    std::shared_ptr<SqlOperator::InterfaceOperator> whereStatement = OR(IS("first_name", std::string("Peter")), IS("first_name", "Jacques"));
    DatabaseManager::SearchOption searchOption = {"Persons", whereStatement, 10, 0, "first_name"};
    std::vector<BookManager::Entity::Person> deserializedTable = sut->searchPerson(searchOption);

    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testSearchPersonWhere_Role)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator},
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator}};

    DatabaseManager::SearchOption searchOption = {"Persons", IS("role", 2), 10, 0, "last_name"};
    std::vector<BookManager::Entity::Person> deserializedTable = sut->searchPerson(searchOption);

    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testSearchPublisher)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {3, "Pocket"},
        {2, "Mu"},
        {1, "12-25"}
    };

    DatabaseManager::SearchOption searchOption = {"Publishers", nullptr, 10, 0, "name", QueryBuilder::Order::DESCENDANT};
    std::vector<BookManager::Entity::Publisher> deserializedTable = sut->searchPublisher(searchOption);

    expectIdAndName<BookManager::Entity::Publisher>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testSearchCategory)
{
    std::vector<BookManager::Category::Category> expectedDeserializedTable{
        {5, "Bit-lit"},
        {3, "Fantasy"},
        {2, "Sci-Fi"},
        {1, "Thriller"},
        {4, "Young Adult"}};
    DatabaseManager::SearchOption searchOption = {"Categories", nullptr, 10, 0, "name", QueryBuilder::Order::ASCENDANT};
    std::vector<BookManager::Category::Category> deserializedTable = sut->searchCategory(searchOption);

    expectIdAndName<BookManager::Category::Category>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testSearchBookSeries)
{
    std::vector<BookManager::Entity::BookSeries> expectedDeserializedTable{
        {1, "Harry Potter"},
        {4, "Hunger Games"},
        {2, "Seigneur des Anneaux"},
        {3, "Star Wars"}};
    DatabaseManager::SearchOption searchOption = {"BookSeries", nullptr, 10, 0, "name", QueryBuilder::Order::ASCENDANT};
    std::vector<BookManager::Entity::BookSeries> deserializedTable = sut->searchBookSeries(searchOption);

    expectIdAndName<BookManager::Entity::BookSeries>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testSearchBook)
{
    initBookFactoryMaillon();
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable{};

    std::shared_ptr<BookManager::Book::Abstraction::Book> book_ArtBookToyStory1 = DatabaseManagerTestCommon::initBookTestNoOptionalField();
    expectedDeserializedTable.push_back(book_ArtBookToyStory1);

    std::shared_ptr<BookManager::Book::Abstraction::Book> book_ArtBookToyStory2 = DatabaseManagerTestCommon::initBookTestWithBookSeries();
    expectedDeserializedTable.push_back(book_ArtBookToyStory2);

    std::shared_ptr<BookManager::Book::Abstraction::Book> book_Batman = DatabaseManagerTestCommon::initBookTestPtrNotSet();
    expectedDeserializedTable.push_back(book_Batman);

    std::shared_ptr<BookManager::Book::Abstraction::Book> book_testBook = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    expectedDeserializedTable.push_back(book_testBook);

    DatabaseManager::SearchOption searchOption = {"Books", nullptr, 10, 0, "title", QueryBuilder::Order::ASCENDANT};
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable = sut->searchBook(searchOption);

    expectBookTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testSearchBookWhereLike_Artbook)
{
    initBookFactoryMaillon();
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable{};

    std::shared_ptr<BookManager::Book::Abstraction::Book> book_ArtBookToyStory1 = DatabaseManagerTestCommon::initBookTestNoOptionalField();
    expectedDeserializedTable.push_back(book_ArtBookToyStory1);

    std::shared_ptr<BookManager::Book::Abstraction::Book> book_ArtBookToyStory2 = DatabaseManagerTestCommon::initBookTestWithBookSeries();
    expectedDeserializedTable.push_back(book_ArtBookToyStory2);

    DatabaseManager::SearchOption searchOption = {"Books", LIKE("title", "ArtBook%"), 10, 0, "title", QueryBuilder::Order::ASCENDANT};
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable = sut->searchBook(searchOption);

    expectBookTable(deserializedTable, expectedDeserializedTable);
}