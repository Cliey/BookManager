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
                {}

                bool updatePerson(BookManager::Entity::Person);
                bool updatePublisher(BookManager::Entity::Publisher);
                bool updateCategory(BookManager::Category::Category);
                bool updateBookSerie(BookManager::Entity::BookSerie);
                bool updateBook(std::shared_ptr<BookManager::Book::Abstraction::Book>);

            private:
                void bindOptionalDate(SQLite::Statement&, std::string, std::optional<time_t>);
                std::string convertDateToString(std::time_t);
                template<typename T>
                void bindPointersTypeForId(SQLite::Statement&, std::string, std::shared_ptr<T>);
                template<typename T, typename U>
                void bindPointersType(SQLite::Statement&, std::string, std::shared_ptr<T>, std::function<U(std::shared_ptr<T>)> const);

                void updateBooksPersonsTable(int, std::vector<std::shared_ptr<Entity::Person>>);
                void updateBooksSubCategoriesTable(int, std::vector<std::shared_ptr<Category::Category>>);


                std::shared_ptr<SQLite::Database> database;
        };

        template<typename T>
        void TableUpdater::bindPointersTypeForId(SQLite::Statement& query, std::string bindName, std::shared_ptr<T> value)
        {
            if(value)
                query.bind(bindName, value->getId());
            else
                query.bind(bindName); // bind to null
        }
        template<typename T, typename U>
        void TableUpdater::bindPointersType(
            SQLite::Statement& query, std::string bindName, std::shared_ptr<T> value, std::function<U(std::shared_ptr<T>)> const func)
        {
            if(value)
                query.bind(bindName, func(value));
            else
                query.bind(bindName); // bind to null
        }

    } // namespace Manager
} // namespace BookManager