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


class DatabaseManagerTestCommon : public ::testing::Test
{
public:
    DatabaseManagerTestCommon()
    {
        static bool alreadyInit = true;
        if(!alreadyInit)
        {
            initDbTest();
            alreadyInit = true;
        }

        sut = DatabaseManager::getDbManager();
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

    std::shared_ptr<DatabaseManager> sut;

private:
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
                        first_name TEXT NOT NULL,\
                        last_name TEXT NOT NULL,\
                        role INTEGER NOT NULL)"); // OK

        db.exec("CREATE TABLE BookSeries(\
                        id INTEGER PRIMARY KEY NOT NULL,\
                        name TEXT NOT NULL)");

        db.exec("CREATE TABLE Categories(\
                        id INTEGER PRIMARY KEY NOT NULL,\
                        name TEXT NOT NULL)"); // OK

        db.exec("CREATE TABLE Books(\
                        id INT PRIMARY KEY NOT NULL,\
                        type INT NOT NULL /*-- or text ? */, \
                        title TEXT NOT NULL,\
                        /* author */\
                        main_category INT,\
                        /* Subcategory */\
                        publisher INT,\
                        book_serie INT,\
                        published_date TEXT NOT NULL /* (YYYY-MM-DD) */,\
                        purchased_date TEXT /* (YYYY-MM-DD) */,\
                        price REAL CHECK(price > 0),\
                        status INT DEFAULT 0,\
                        is_read BOOLEAN DEFAULT false NOT NULL /* 0 False / 1 True or INT DEFAULT 0 */,\
                        start_reading_date TEXT /* (YYYY-MM-DD) */,\
                        end_reading_date TEXT /* (YYYY-MM-DD) */,\
                        rate INT DEFAULT NULL,\
                        FOREIGN KEY(main_category) REFERENCES Categories(id)\
                                ON UPDATE cascade\
                                ON DELETE set null,\
                        FOREIGN KEY(publisher) REFERENCES Publishers(id)\
                                ON UPDATE cascade\
                                ON DELETE set null,\
                        FOREIGN KEY(book_serie) REFERENCES BookSeries(id)\
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

        db.exec("CREATE TABLE Books_SubCategories(\
                        bookId INT NOT NULL,\
                        subCategoryId INT NOT NULL,\
                        FOREIGN KEY(bookId) REFERENCES Books(id)\
                            ON UPDATE cascade\
                            ON DELETE cascade,\
                        FOREIGN KEY(subCategoryId) REFERENCES Categories(id)\
                            ON UPDATE cascade\
                            ON DELETE cascade)"); // OK
        db.exec("INSERT INTO Persons (\"id\", \"first_name\", \"last_name\", \"role\") VALUES ('1', 'Jacques', 'Edouard', '1')");
        db.exec("INSERT INTO Persons (\"id\", \"first_name\", \"last_name\", \"role\") VALUES ('2', 'Charles', 'Henry', '2')");
        db.exec("INSERT INTO Persons (\"id\", \"first_name\", \"last_name\", \"role\") VALUES ('3', 'Peter', 'Jackson', '1')");
        db.exec("INSERT INTO Persons (\"id\", \"first_name\", \"last_name\", \"role\") VALUES ('4', 'Richard', 'Bordo', '2')");

        db.exec("INSERT INTO Publishers (\"id\", \"name\") VALUES ('1', '12-25')");
        db.exec("INSERT INTO Publishers (\"id\", \"name\") VALUES ('2', 'Mu')");
        db.exec("INSERT INTO Publishers (\"id\", \"name\") VALUES ('3', 'Pocket')");

        db.exec("INSERT INTO BookSeries (\"id\", \"name\") VALUES ('1', 'Harry Potter')");
        db.exec("INSERT INTO BookSeries (\"id\", \"name\") VALUES ('2', 'Seigneur des Anneaux')");
        db.exec("INSERT INTO BookSeries (\"id\", \"name\") VALUES ('3', 'Star Wars')");
        db.exec("INSERT INTO BookSeries (\"id\", \"name\") VALUES ('4', 'Hunger Games')");

        db.exec("INSERT INTO Categories (\"id\", \"name\") VALUES ('1', 'Thriller')");
        db.exec("INSERT INTO Categories (\"id\", \"name\") VALUES ('2', 'Sci-Fi')");
        db.exec("INSERT INTO Categories (\"id\", \"name\") VALUES ('3', 'Fantasy')");
        db.exec("INSERT INTO Categories (\"id\", \"name\") VALUES ('4', 'Young Adult')");

        db.exec("INSERT INTO Books (\"id\", \"type\", \"title\", \"main_category\", \"publisher\", \"published_date\", \"is_read\") VALUES ('1', '0', 'ArtBook Toy Story', '1', '1', '2017-02-04', '0')");
        db.exec("INSERT INTO Books (\"id\", \"type\", \"title\", \"main_category\", \"publisher\", \"book_serie\", \"published_date\", \"purchased_date\", \"price\", \"status\", \"is_read\", \"start_reading_date\", \"end_reading_date\", \"rate\") VALUES ('2', '3', 'TestBook', '2', '2', '3', '2018-07-21', '2019-12-04', '3.7', '2', '1', '2020-01-04', '2020-02-07', '8')");

        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('1', '1')");
        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('2', '1')");
        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('2', '3')");

        db.exec("INSERT INTO Books_SubCategories (\"bookId\", \"subCategoryId\") VALUES ('2', '4')");
        db.exec("INSERT INTO Books_SubCategories (\"bookId\", \"subCategoryId\") VALUES ('2', '3')");
    }

    void expectPersonTableOneElement(BookManager::Entity::Person deserializedElement, BookManager::Entity::Person expectedDeserializedElement)
    {
            EXPECT_EQ(deserializedElement.getId(), expectedDeserializedElement.getId());
            EXPECT_EQ(deserializedElement.getFirstName(), expectedDeserializedElement.getFirstName());
            EXPECT_EQ(deserializedElement.getLastName(), expectedDeserializedElement.getLastName());
            EXPECT_EQ(deserializedElement.getRole(), expectedDeserializedElement.getRole());
    }
};