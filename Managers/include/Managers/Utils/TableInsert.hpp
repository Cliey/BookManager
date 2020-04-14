#pragma once
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <string>
#include <ctime>
#include <optional>
#include <functional>

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
        namespace Abstraction
        {
            class Book;
        }
    }

    namespace Manager
    {
        class TableInsert
        {
            public:
                TableInsert(std::shared_ptr<SQLite::Database> database) : database(database)
                {}

                bool addPerson(BookManager::Entity::Person);
                bool addPublisher(BookManager::Entity::Publisher);
                bool addCategory(BookManager::Category::Category);
                bool addBookSerie(BookManager::Entity::BookSerie);
                bool addBook(std::shared_ptr<BookManager::Book::Abstraction::Book>);

            private:
                void bindOptionalDate(SQLite::Statement&, std::string, std::optional<time_t>);
                std::string convertDateToString(std::time_t);
                template<typename T>
                void bindPointersTypeForId(SQLite::Statement&, std::string, std::shared_ptr<T>);
                template<typename T, typename U>
                void bindPointersType(SQLite::Statement&, std::string, std::shared_ptr<T>, std::function<U(std::shared_ptr<T>)> const);

                void addBooksPersonsTable(int, std::vector<std::shared_ptr<Entity::Person>>);
                void addBooksSubCategoriesTable(int, std::vector<std::shared_ptr<Category::Category>>);
                void deleteInBooksSubCategoriesTable(int bookId);
                void deleteInBooksPersonsTable(int bookId);
                void deleteInBooksTable(int bookId);
                void deleteBookEntryInTable(std::string table, int bookId);


                std::shared_ptr<SQLite::Database> database;
        };

        template<typename T>
        void TableInsert::bindPointersTypeForId(SQLite::Statement& query, std::string bindName, std::shared_ptr<T> value)
        {
            if(value)
                query.bind(bindName, value->getId());
            else
                query.bind(bindName); // bind to null
        }
        template<typename T, typename U>
        void TableInsert::bindPointersType(
            SQLite::Statement& query, std::string bindName, std::shared_ptr<T> value, std::function<U(std::shared_ptr<T>)> const func)
        {
            if(value)
                query.bind(bindName, func(value));
            else
                query.bind(bindName); // bind to null
        }

    } // namespace Manager
} // namespace BookManager