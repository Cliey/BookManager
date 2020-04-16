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
        class TableDelete
        {
            public:
                TableDelete(std::shared_ptr<SQLite::Database> database) : database(database)
                {}

                bool deleteInPersonTable(int, bool);
                bool deleteInPublisherTable(int, bool);
                bool deleteInCategoryTable(int, bool);
                bool deleteInBookSerieTable(int, bool);
                bool deleteInBooksTable(int);

            private:
                bool deleteInBooksSubCategoriesTable(int);
                bool deleteInBooksPersonsTable(int);

                std::shared_ptr<SQLite::Database> database;
        };

    } // namespace Manager
} // namespace BookManager