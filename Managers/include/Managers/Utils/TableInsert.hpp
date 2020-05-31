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

                std::tuple<bool, int> addPerson(BookManager::Entity::Person);
                std::tuple<bool, int> addPublisher(BookManager::Entity::Publisher);
                std::tuple<bool, int> addCategory(BookManager::Category::Category);
                std::tuple<bool, int> addBookSeries(BookManager::Entity::BookSeries);
                std::tuple<bool, int> addBook(std::shared_ptr<BookManager::Book::Abstraction::Book>);

            private:
                int getLastIdAddedInTable(std::string table);
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