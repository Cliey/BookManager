#pragma once
#include <gtest/gtest.h>
#include <cstdio>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include "BookAbstract/Book.hpp"
#include "EntityTypes/BookSerie.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "../../Category.hpp"
#include "BookTypes/Novel.hpp"
#include "BookTypes/Artbook.hpp"
#include "BookTypes/Comics.hpp"
#include "BookFactory/BookFactory.hpp"

class DatabaseManagerTestCommon : public ::testing::Test
{
public:
    static void initDbTest()
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
                        id INTEGER PRIMARY KEY NOT NULL,\
                        type INTEGER NOT NULL /*-- or text ? */, \
                        title TEXT NOT NULL,\
                        /* author */\
                        main_category INTEGER,\
                        /* Subcategory */\
                        publisher INTEGER,\
                        book_serie INTEGER,\
                        published_date TEXT NOT NULL /* (YYYY-MM-DD) */,\
                        purchased_date TEXT /* (YYYY-MM-DD) */,\
                        price REAL CHECK(price > 0),\
                        status INTEGER DEFAULT 0,\
                        is_read BOOLEAN DEFAULT false NOT NULL /* 0 False / 1 True or INTEGER DEFAULT 0 */,\
                        start_reading_date TEXT /* (YYYY-MM-DD) */,\
                        end_reading_date TEXT /* (YYYY-MM-DD) */,\
                        rate INTEGER DEFAULT NULL,\
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
                        bookId INTEGER NOT NULL,\
                        personId INTEGER NOT NULL,\
                        FOREIGN KEY(bookId) REFERENCES Books(id)\
                            ON UPDATE cascade\
                            ON DELETE cascade,\
                        FOREIGN KEY(personId) REFERENCES Persons(id)\
                            ON UPDATE cascade\
                            ON DELETE cascade)"); // OK

        db.exec("CREATE TABLE Books_SubCategories(\
                        bookId INTEGER NOT NULL,\
                        subCategoryId INTEGER NOT NULL,\
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
        db.exec("INSERT INTO Categories (\"id\", \"name\") VALUES ('5', 'Bit-Lit')");

        db.exec("INSERT INTO Books (\"id\", \"type\", \"title\", \"main_category\", \"publisher\", \"published_date\", \"is_read\") VALUES ('1', '0', 'ArtBook Toy Story', '1', '1', '2017-02-04', '0')");
        db.exec("INSERT INTO Books (\"id\", \"type\", \"title\", \"main_category\", \"publisher\", \"book_serie\", \"published_date\", \"purchased_date\", \"price\", \"status\", \"is_read\", \"start_reading_date\", \"end_reading_date\", \"rate\") VALUES ('2', '3', 'TestBook', '2', '2', '3', '2018-07-21', '2019-12-04', '3.7', '2', '1', '2020-01-04', '2020-02-07', '8')");
        db.exec("INSERT INTO Books (\"id\", \"type\", \"title\", \"main_category\", \"publisher\", \"book_serie\", \"published_date\", \"is_read\") VALUES ('3', '0', 'ArtBook Toy Story 2', '3', '1', '1', '2017-02-04', '0')");

        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('1', '1')");
        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('2', '1')");
        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('2', '3')");
        db.exec("INSERT INTO Books_Persons (\"bookId\", \"personId\") VALUES ('3', '3')");

        db.exec("INSERT INTO Books_SubCategories (\"bookId\", \"subCategoryId\") VALUES ('2', '4')");
        db.exec("INSERT INTO Books_SubCategories (\"bookId\", \"subCategoryId\") VALUES ('2', '3')");
    }

    static std::shared_ptr<BookManager::Book::Abstraction::Book> initBookTestNoOptionalField()
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

    static std::shared_ptr<BookManager::Book::Abstraction::Book> initBookTestAllOptionalField()
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

    static std::shared_ptr<BookManager::Book::Abstraction::Book> initBookTestWithBookSerie()
    {
        std::shared_ptr<BookManager::Book::Abstraction::Book> book = std::make_shared<BookManager::Book::Artbook>();
        book->id = 3;
        book->title = "ArtBook Toy Story 2";
        std::vector<std::shared_ptr<BookManager::Entity::Person>> authorsVector;
        std::shared_ptr<BookManager::Entity::Person> authorJacquesEdouard =  initAuthor(3, "Peter", "Jackson", BookManager::Entity::Role::Author);
        authorsVector.push_back(authorJacquesEdouard);
        book->author = authorsVector;
        book->mainCategory = std::make_shared<BookManager::Category::Category>(3, "Fantasy");
        book->publisher = std::make_shared<BookManager::Entity::Publisher>(1, "12-25");
        book->published = std::make_optional<std::time_t>(initDate(2017, 2, 4));
        book->bookSerie = std::make_shared<BookManager::Entity::BookSerie>(1, "Harry Potter");
        book->isRead = false;
        return book;
    }

    static void checkLogOutput(std::string output, std::string expectedLog)
    {
        auto logFound = output.find(expectedLog);

        std::cout << output << std::endl;
        EXPECT_TRUE(logFound != std::string::npos);
    }

private:
    static std::time_t initDate(int year, int month, int day)
    {
        std::tm date{};
        date.tm_year = year - 1900; // Year since 1900
        date.tm_mon = month - 1; // 0 tu 11
        date.tm_mday = day;
        return (std::mktime(&date));
    }

    static std::shared_ptr<BookManager::Entity::Person> initAuthor(int id, std::string firstName, std::string lastName, BookManager::Entity::Role role)
    {
        return std::make_shared<BookManager::Entity::Person>(id, firstName, lastName, role);
    }
};