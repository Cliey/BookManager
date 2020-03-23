#include "Managers/DatabaseManager.hpp"
#include "BookAbstract/Book.hpp"
#include "EntityTypes/BookSerie.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
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
        static bool alreadyInit = true;
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
                        /* statut (integer? 1 a 3 check) */\
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
    }

    // std::string getLogMessage(std::string logOutput)
    // {
    //     return (strrchr(logOutput.c_str(), '-') + 2);
    // }

    void expectPersonTable(std::vector<BookManager::Entity::Person> deserializedTable, std::vector<BookManager::Entity::Person> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            EXPECT_EQ(deserializedTable[i].getId(), expectedDeserializedTable[i].getId());
            EXPECT_EQ(deserializedTable[i].getFirstName(), expectedDeserializedTable[i].getFirstName());
            EXPECT_EQ(deserializedTable[i].getLastName(), expectedDeserializedTable[i].getLastName());
            EXPECT_EQ(deserializedTable[i].getRole(), expectedDeserializedTable[i].getRole());
        }
    }

    template<class T> void expectIdAndName(std::vector<T> deserializedTable, std::vector<T> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            EXPECT_EQ(deserializedTable[i].getId(), expectedDeserializedTable[i].getId());
            EXPECT_EQ(deserializedTable[i].getName(), expectedDeserializedTable[i].getName());
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

