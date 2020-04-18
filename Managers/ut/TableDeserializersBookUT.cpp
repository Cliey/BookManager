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
            std::cout << " i = " << i << std::endl;
            EXPECT_EQ(deserializedTable[i]->getType(), expectedDeserializedTable[i]->getType());
            EXPECT_EQ(deserializedTable[i]->id, expectedDeserializedTable[i]->id);
            EXPECT_EQ(deserializedTable[i]->generalInfo.title, expectedDeserializedTable[i]->generalInfo.title);
            expectPersonTable(deserializedTable[i]->generalInfo.author, expectedDeserializedTable[i]->generalInfo.author);
            expectOneIdAndName<BookManager::Entity::Publisher>(deserializedTable[i]->generalInfo.publisher, expectedDeserializedTable[i]->generalInfo.publisher);
            expectOneIdAndName<BookManager::Entity::BookSerie>(deserializedTable[i]->generalInfo.bookSerie, expectedDeserializedTable[i]->generalInfo.bookSerie);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->generalInfo.published, expectedDeserializedTable[i]->generalInfo.published);
            expectOneIdAndName<BookManager::Category::Category>(deserializedTable[i]->categoryInfo.mainCategory, expectedDeserializedTable[i]->categoryInfo.mainCategory);
            expectIdAndName<BookManager::Category::Category>(deserializedTable[i]->categoryInfo.subCategory, expectedDeserializedTable[i]->categoryInfo.subCategory);

            CheckOptionalField::check<std::time_t>(deserializedTable[i]->statInfo.purchasedDate, expectedDeserializedTable[i]->statInfo.purchasedDate);
            CheckOptionalField::check<double>(deserializedTable[i]->statInfo.price, expectedDeserializedTable[i]->statInfo.price);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->statInfo.startReadingDate, expectedDeserializedTable[i]->statInfo.startReadingDate);
            CheckOptionalField::check<std::time_t>(deserializedTable[i]->statInfo.endReadingDate, expectedDeserializedTable[i]->statInfo.endReadingDate);
            EXPECT_EQ(deserializedTable[i]->additionalInfo.isRead, expectedDeserializedTable[i]->additionalInfo.isRead);
            EXPECT_EQ(deserializedTable[i]->additionalInfo.status, expectedDeserializedTable[i]->additionalInfo.status);
            EXPECT_EQ(deserializedTable[i]->additionalInfo.rate, expectedDeserializedTable[i]->additionalInfo.rate);
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

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTestPtrNotSet = DatabaseManagerTestCommon::initBookTestPtrNotSet();
    expectedDeserializedTable.push_back(bookTestPtrNotSet);

    if(bookTestPtrNotSet->generalInfo.bookSerie)
        std::cout << "bookSerie set" << std::endl;

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