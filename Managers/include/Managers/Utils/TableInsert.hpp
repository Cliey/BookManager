#pragma once
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <string>
#include <ctime>
#include <optional>
#include <functional>
#include "Managers/Utils/TableModifier.hpp"

namespace BookManager
{
    namespace Entity
    {
        class BookSeries;
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
                {
                    tableModifier = std::make_shared<TableModifier>();
                }

                bool addPerson(BookManager::Entity::Person);
                bool addPublisher(BookManager::Entity::Publisher);
                bool addCategory(BookManager::Category::Category);
                bool addBookSeries(BookManager::Entity::BookSeries);
                bool addBook(std::shared_ptr<BookManager::Book::Abstraction::Book>);

            private:
                void addBooksPersonsTable(int, std::vector<std::shared_ptr<Entity::Person>>);
                void addBooksSubCategoriesTable(int, std::vector<std::shared_ptr<Category::Category>>);
                void deleteInBooksSubCategoriesTable(int bookId);
                void deleteInBooksPersonsTable(int bookId);
                void deleteInBooksTable(int bookId);


                std::shared_ptr<SQLite::Database> database;
                std::shared_ptr<TableModifier> tableModifier;
        };

    } // namespace Manager
} // namespace BookManager