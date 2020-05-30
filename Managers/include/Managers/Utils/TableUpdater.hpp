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
        class TableUpdater
        {
            public:
                TableUpdater(std::shared_ptr<SQLite::Database> database) : database(database)
                {
                    tableModifier = std::make_shared<TableModifier>();
                }

                bool updatePerson(BookManager::Entity::Person);
                bool updatePublisher(BookManager::Entity::Publisher);
                bool updateCategory(BookManager::Category::Category);
                bool updateBookSeries(BookManager::Entity::BookSeries);
                bool updateBook(std::shared_ptr<BookManager::Book::Abstraction::Book>);

            private:
                SQLite::Statement createQueryAndBindId(std::string, int);
                void updateBooksPersonsTable(int, std::vector<std::shared_ptr<Entity::Person>>);
                void updateBooksSubCategoriesTable(int, std::vector<std::shared_ptr<Category::Category>>);


                std::shared_ptr<SQLite::Database> database;
                std::shared_ptr<TableModifier> tableModifier;
        };
    } // namespace Manager
} // namespace BookManager