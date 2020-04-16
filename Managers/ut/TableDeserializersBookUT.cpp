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

    void expectBookTable(std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable, std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable)
    {
        ASSERT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
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
};

TEST_F(TableDeserializersBookTest, testGetBookVectorNoOffset)
{
    initBookFactoryMaillon();
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable{};

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTestNoOptionalField = DatabaseManagerTestCommon::initBookTestNoOptionalField();
    expectedDeserializedTable.push_back(bookTestNoOptionalField);

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTestAllOptionalField = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    expectedDeserializedTable.push_back(bookTestAllOptionalField);

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTestWithBookSerie = DatabaseManagerTestCommon::initBookTestWithBookSerie();
    expectedDeserializedTable.push_back(bookTestWithBookSerie);

    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable;
    deserializedTable = sut->deserializeBookTable(4, 0);
    expectBookTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersBookTest, testGetBookVectorWithOffset)
{
    initBookFactoryMaillon();
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable{};

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTestAllOptionalField = DatabaseManagerTestCommon::initBookTestAllOptionalField();
    expectedDeserializedTable.push_back(bookTestAllOptionalField);
    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTestWithBookSerie = DatabaseManagerTestCommon::initBookTestWithBookSerie();
    expectedDeserializedTable.push_back(bookTestWithBookSerie);

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