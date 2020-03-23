#include "Managers/DatabaseManager.hpp"
#include "BookAbstract/Book.hpp"
#include "EntityTypes/BookSerie.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"

#include "MaillonCreation/BookCreationResponsibility.hpp"
#include "MaillonCreation/MaillonCreationBookArtBook.hpp"
#include "MaillonCreation/MaillonCreationBookNovel.hpp"
#include "MaillonCreation/MaillonCreationBookComics.hpp"
#include "MaillonCreation/MaillonCreationBookManga.hpp"
#include "BookFactory/BookFactory.hpp"
#include "../../Category.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <cstdio>

using namespace BookManager::Manager;
using namespace BookManager::Book;

class DatabaseManagerTest : public ::testing::Test
{
public:
    DatabaseManagerTest()
    {
        static bool alreadyInit = false;
        if(!alreadyInit)
        {
            initDbTest();
            alreadyInit = true;
        }

        sut = DatabaseManager::getDbManager();
    }

    void initDbTest()
    {
        if( remove("./data/BookManager.db") != 0 )
            std::cout << "Error deleting file" << std::endl;
        else
            std::cout << "File successfully deleted" << std::endl;

        SQLite::Database db("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db.exec("CREATE TABLE Publishers(\
                        id INTEGER PRIMARY KEY NOT NULL,\
                        name TEXT NOT NULL)"); // OK

        db.exec("CREATE TABLE Persons(\
                        id INTEGER PRIMARY KEY NOT NULL,\
                        firstName TEXT NOT NULL,\
                        lastName TEXT NOT NULL,\
                        role INTEGER NOT NULL)"); // OK

        db.exec("CREATE TABLE BookSeries(\
                        id INTEGER PRIMARY KEY NOT NULL,\
                        name TEXT NOT NULL)"); // add BookVector ? BookId Vector ?

        db.exec("CREATE TABLE Category(\
                        id INTEGER PRIMARY KEY NOT NULL,\
                        name TEXT NOT NULL)"); // OK

        db.exec("CREATE TABLE Books(\
                        id INT PRIMARY KEY NOT NULL,\
                        type INT NOT NULL /*-- or text ? */, \
                        title TEXT NOT NULL,\
                        /* author */\
                        mainCategoryId INT,\
                        /* Subcategory */\
                        publisherId INT,\
                        bookSerieId INT,\
                        publishedDate TEXT NOT NULL /* (YYYY-MM-DD) */,\
                        purchasedDate TEXT /* (YYYY-MM-DD) */,\
                        price REAL CHECK(price > 0),\
                        status INT DEFAULT 0,\
                        isRead BOOLEAN DEFAULT false NOT NULL /* 0 False / 1 True or INT DEFAULT 0 */,\
                        startReadingDate TEXT /* (YYYY-MM-DD) */,\
                        endReadingDate TEXT /* (YYYY-MM-DD) */,\
                        rate INT DEFAULT NULL,\
                        FOREIGN KEY(mainCategoryId) REFERENCES Category(id)\
                                ON UPDATE cascade\
                                ON DELETE set null,\
                        FOREIGN KEY(publisherId) REFERENCES Publishers(id)\
                                ON UPDATE cascade\
                                ON DELETE set null,\
                        FOREIGN KEY(bookSerieId) REFERENCES BookSeries(id)\
                                ON UPDATE cascade\
                                ON DELETE set null)"); // Not finished

        db.exec("CREATE TABLE Books_Persons(\
                        bookId INT NOT NULL,\
                        personId INT NOT NULL,\
                        FOREIGN KEY(bookId) REFERENCES Books(id)\
                            ON UPDATE cascade\
                            ON DELETE cascade,\
                        FOREIGN KEY(personId) REFERENCES Persons(id)\
                            ON UPDATE cascade\
                            ON DELETE cascade)"); // OK

        db.exec("CREATE TABLE Books_SubCategory(\
                        bookId INT NOT NULL,\
                        subCategoryId INT NOT NULL,\
                        FOREIGN KEY(bookId) REFERENCES Books(id)\
                            ON UPDATE cascade\
                            ON DELETE cascade,\
                        FOREIGN KEY(subCategoryId) REFERENCES Category(id)\
                            ON UPDATE cascade\
                            ON DELETE cascade)"); // OK
        db.exec("INSERT INTO Persons (\"id\", \"firstName\", \"lastName\", \"role\") VALUES ('1', 'Jacques', 'Edouard', '1')");
        db.exec("INSERT INTO Persons (\"id\", \"firstName\", \"lastName\", \"role\") VALUES ('2', 'Charles', 'Henry', '2')");
        db.exec("INSERT INTO Persons (\"id\", \"firstName\", \"lastName\", \"role\") VALUES ('3', 'Peter', 'Jackson', '1')");
        db.exec("INSERT INTO Persons (\"id\", \"firstName\", \"lastName\", \"role\") VALUES ('4', 'Richard', 'Bordo', '2')");

        db.exec("INSERT INTO Publishers (\"id\", \"name\") VALUES ('1', '12-25')");
        db.exec("INSERT INTO Publishers (\"id\", \"name\") VALUES ('2', 'Mu')");
        db.exec("INSERT INTO Publishers (\"id\", \"name\") VALUES ('3', 'Pocket')");

        db.exec("INSERT INTO BookSeries (\"id\", \"name\") VALUES ('1', 'Harry Potter')");
        db.exec("INSERT INTO BookSeries (\"id\", \"name\") VALUES ('2', 'Seigneur des Anneaux')");
        db.exec("INSERT INTO BookSeries (\"id\", \"name\") VALUES ('3', 'Star Wars')");
        db.exec("INSERT INTO BookSeries (\"id\", \"name\") VALUES ('4', 'Hunger Games')");

        db.exec("INSERT INTO Category (\"id\", \"name\") VALUES ('1', 'Thriller')");
        db.exec("INSERT INTO Category (\"id\", \"name\") VALUES ('2', 'Sci-Fi')");
        db.exec("INSERT INTO Category (\"id\", \"name\") VALUES ('3', 'Fantasy')");
        db.exec("INSERT INTO Category (\"id\", \"name\") VALUES ('4', 'Young Adult')");

        db.exec("INSERT INTO Books (\"id\", \"type\", \"title\", \"mainCategoryId\", \"publisherId\", \"publishedDate\", \"isRead\") VALUES ('1', '0', 'ArtBook Toy Story', '1', '1', '2017-02-04', '0')");
        db.exec("INSERT INTO Books (\"id\", \"type\", \"title\", \"mainCategoryId\", \"publisherId\", \"bookSerieId\", \"publishedDate\", \"purchasedDate\", \"price\", \"status\", \"isRead\", \"startReadingDate\", \"endReadingDate\", \"rate\") VALUES ('2', '3', 'TestBook', '2', '2', '3', '2018-07-21', '2019-12-04', '3.7', '2', '1', '2020-01-04', '2020-02-07', '8')");

        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('1', '1')");
        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('2', '1')");
        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('2', '3')");

        db.exec("INSERT INTO Books_SubCategory (\"bookId\", \"subCategoryId\") VALUES ('2', '4')");
        db.exec("INSERT INTO Books_SubCategory (\"bookId\", \"subCategoryId\") VALUES ('2', '3')");
    }

    void initBookFactoryMaillon()
    {
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookArtBook>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookNovel>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookComics>());
        BookFactory::append(std::make_unique<BookManager::Book::Utils::MaillonCreationBookManga>());
    }

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

    std::shared_ptr<BookManager::Book::Abstraction::Book> initBookTest2()
    {
        std::shared_ptr<BookManager::Book::Abstraction::Book> book = std::make_shared<BookManager::Book::Artbook>();
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
        // book->subCategory = 1;
        book->publisher = std::make_shared<BookManager::Entity::Publisher>(1, "12-25");
        book->published = std::make_optional<std::time_t>(initDate(2017, 2, 4));
        book->isRead = false;
        return book;
    }

    void expectPersonTableOneElement(BookManager::Entity::Person deserializedElement, BookManager::Entity::Person expectedDeserializedElement)
    {
            EXPECT_EQ(deserializedElement.getId(), expectedDeserializedElement.getId());
            EXPECT_EQ(deserializedElement.getFirstName(), expectedDeserializedElement.getFirstName());
            EXPECT_EQ(deserializedElement.getLastName(), expectedDeserializedElement.getLastName());
            EXPECT_EQ(deserializedElement.getRole(), expectedDeserializedElement.getRole());
    }

    void expectPersonTable(std::vector<BookManager::Entity::Person> deserializedTable, std::vector<BookManager::Entity::Person> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            expectPersonTableOneElement(deserializedTable[i], expectedDeserializedTable[i]);
        }
    }

    void expectPersonTable(std::vector<std::shared_ptr<BookManager::Entity::Person>> deserializedTable, std::vector<std::shared_ptr<BookManager::Entity::Person>> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            EXPECT_EQ(deserializedTable[i] == nullptr, expectedDeserializedTable[i] == nullptr);
            if(deserializedTable[i])
            {
                expectPersonTableOneElement(*deserializedTable[i], *expectedDeserializedTable[i]);
            }
        }
    }

    template<class T> void expectIdAndName(std::vector<T> deserializedTable, std::vector<T> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            expectOneIdAndName<T>(deserializedTable[i], expectedDeserializedTable[i]);
        }
    }

    template<class T> void expectIdAndName(std::vector<std::shared_ptr<T>> deserializedTable, std::vector<std::shared_ptr<T>> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            expectOneIdAndName<T>(deserializedTable[i], expectedDeserializedTable[i]);
        }
    }

    template<class T> void expectOneIdAndName(T deserializedElement, T expectedDeserializedElement)
    {
        EXPECT_EQ(deserializedElement.getId(), expectedDeserializedElement.getId());
        EXPECT_EQ(deserializedElement.getName(), expectedDeserializedElement.getName());
    }

    template<class T> void expectOneIdAndName(std::shared_ptr<T> deserializedElement, std::shared_ptr<T> expectedDeserializedElement)
    {
        EXPECT_EQ(deserializedElement == nullptr, expectedDeserializedElement == nullptr);
        if(deserializedElement)
        {
            expectOneIdAndName(*deserializedElement, *expectedDeserializedElement);
        }
    }


    void expectBookTable(std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable, std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            std::cout << "Book = " << i << std::endl;
            EXPECT_EQ(deserializedTable[i]->id, expectedDeserializedTable[i]->id);
            EXPECT_EQ(deserializedTable[i]->title, expectedDeserializedTable[i]->title);
            expectPersonTable(deserializedTable[i]->author, expectedDeserializedTable[i]->author);
            expectOneIdAndName<BookManager::Category::Category>(deserializedTable[i]->mainCategory, expectedDeserializedTable[i]->mainCategory);
            expectIdAndName<BookManager::Category::Category>(deserializedTable[i]->subCategory, expectedDeserializedTable[i]->subCategory);
            expectOneIdAndName<BookManager::Entity::Publisher>(deserializedTable[i]->publisher, expectedDeserializedTable[i]->publisher);
            expectOneIdAndName<BookManager::Entity::BookSerie>(deserializedTable[i]->bookSerie, expectedDeserializedTable[i]->bookSerie);

            checkOptionalField<std::time_t>(deserializedTable[i]->published, expectedDeserializedTable[i]->published);
            checkOptionalField<std::time_t>(deserializedTable[i]->purchasedDate, expectedDeserializedTable[i]->purchasedDate);
            checkOptionalField<double>(deserializedTable[i]->price, expectedDeserializedTable[i]->price);
            EXPECT_EQ(deserializedTable[i]->status, expectedDeserializedTable[i]->status);
            EXPECT_EQ(deserializedTable[i]->isRead, expectedDeserializedTable[i]->isRead);
            checkOptionalField<std::time_t>(deserializedTable[i]->startReadingDate, expectedDeserializedTable[i]->startReadingDate);
            checkOptionalField<std::time_t>(deserializedTable[i]->endReadingDate, expectedDeserializedTable[i]->endReadingDate);
            EXPECT_EQ(deserializedTable[i]->rate, expectedDeserializedTable[i]->rate);
        }
    }

    template <typename T>
    void checkOptionalField(std::optional<T> optionalToCheck, std::optional<T> optionalExpected)
    {
        EXPECT_EQ(optionalToCheck.has_value(), optionalExpected.has_value());
        if(optionalToCheck.has_value())
        {
            EXPECT_EQ(optionalToCheck.value(), optionalExpected.value());
        }
    }

    std::shared_ptr<DatabaseManager> sut;
};

// Person
TEST_F(DatabaseManagerTest, testGetPersonVectorNoOffset)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->getPersonVector(4, 0);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetPersonVectorWithOffset)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->getPersonVector(3, 1);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetPersonVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->getPersonVector(10, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Publisher
TEST_F(DatabaseManagerTest, testGetPublisherVectorNoOffset)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {1, "12-25"},
        {2, "Mu"},
        {3, "Pocket"}};
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->getPublisherVector(3, 0);
    expectIdAndName<BookManager::Entity::Publisher>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetPublisherVectorWithOffset)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {2, "Mu"},
        {3, "Pocket"}};
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->getPublisherVector(3, 1);
    expectIdAndName<BookManager::Entity::Publisher>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetPublisherVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->getPublisherVector(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Category
TEST_F(DatabaseManagerTest, testGetCategoryVectorNoOffset)
{
    std::vector<BookManager::Category::Category> expectedDeserializedTable{
        {1, "Thriller"},
        {2, "Sci-Fi"},
        {3, "Fantasy"},
        {4, "Young Adult"}};
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->getCategoryVector(4, 0);
    expectIdAndName<BookManager::Category::Category>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetCategoryVectorWithOffset)
{
    std::vector<BookManager::Category::Category> expectedDeserializedTable{
        {2, "Sci-Fi"},
        {3, "Fantasy"},
        {4, "Young Adult"}};
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->getCategoryVector(3, 1);
    expectIdAndName<BookManager::Category::Category>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetCategoryVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->getCategoryVector(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Book Series
TEST_F(DatabaseManagerTest, testGetBookSerieVectorNoOffset)
{
    std::vector<BookManager::Entity::BookSerie> expectedDeserializedTable{
        {1, "Harry Potter"},
        {2, "Seigneur des Anneaux"},
        {3, "Star Wars"},
        {4, "Hunger Games"}};
    std::vector<BookManager::Entity::BookSerie> deserializedTable;

    deserializedTable = sut->getBookSerieVector(4, 0);
    expectIdAndName<BookManager::Entity::BookSerie>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetBookSerieVectorWithOffset)
{
    std::vector<BookManager::Entity::BookSerie> expectedDeserializedTable{
        {2, "Seigneur des Anneaux"},
        {3, "Star Wars"},
        {4, "Hunger Games"}};
    std::vector<BookManager::Entity::BookSerie> deserializedTable;

    deserializedTable = sut->getBookSerieVector(3, 1);
    expectIdAndName<BookManager::Entity::BookSerie>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetBookSerieVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::BookSerie> deserializedTable;

    deserializedTable = sut->getBookSerieVector(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Book
TEST_F(DatabaseManagerTest, testGetBookVectorNoOffset)
{
    initBookFactoryMaillon();
    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> expectedDeserializedTable{};

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTest1 = initBookTest1();
    expectedDeserializedTable.push_back(bookTest1);

    std::shared_ptr<BookManager::Book::Abstraction::Book> bookTest2 = initBookTest2();
    expectedDeserializedTable.push_back(bookTest2);

    std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializedTable;
    deserializedTable = sut->getBookVector(4, 0);
    expectBookTable(deserializedTable, expectedDeserializedTable);
}
