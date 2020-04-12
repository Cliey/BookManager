#pragma once
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <string>
#include <ctime>

namespace BookManager
{
    namespace Entity
    {
        class BookSerie;
        class Person;
        class Publisher;
    }
    namespace Category
    {
        class Category;
    }
    namespace Book
	{
        // enum class BookType;
        // enum class BookStatus;
        namespace Abstraction
        {
            class Book;
        }
    }

    namespace Manager
    {
        class TableUpdater
        {
            public:
                TableUpdater(std::shared_ptr<SQLite::Database> database) : database(database)
                {
                    // database = std::make_shared<SQLite::Database>(databaseA->getFilename(), SQLite::OPEN_READWRITE);
                }

                bool updatePerson(BookManager::Entity::Person);
                bool updatePublisher(BookManager::Entity::Publisher);
                bool updateCategory(BookManager::Category::Category);
                bool updateBookSerie(BookManager::Entity::BookSerie);
                bool updateBook(std::shared_ptr<BookManager::Book::Abstraction::Book>);

            private:

                std::shared_ptr<SQLite::Database> database;
        };

    } // namespace Manager
} // namespace BookManager