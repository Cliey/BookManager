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
        class TableModifier
        {
            public:
                TableModifier() = default;

                bool modifyPersonTable(BookManager::Entity::Person, SQLite::Statement&);
                bool modifyPublisherTable(BookManager::Entity::Publisher, SQLite::Statement&);
                bool modifyCategoryTable(BookManager::Category::Category, SQLite::Statement&);
                bool modifyBookSerieTable(BookManager::Entity::BookSerie, SQLite::Statement&);
                int modifyBookTable(std::shared_ptr<BookManager::Book::Abstraction::Book>, SQLite::Statement&);
                void modifyBooksPersonsTable(int, std::vector<std::shared_ptr<Entity::Person>>, SQLite::Statement&);
                void modifyBooksSubCategoriesTable(int, std::vector<std::shared_ptr<Category::Category>>, SQLite::Statement&);
                void deleteInTableWithBookIdBind(int, SQLite::Statement&);

            private:
                void bindString(SQLite::Statement& query, std::string bindName, std::string field);
                std::string convertDateToString(std::time_t);
                template<typename T>
                void bindPointersTypeForId(SQLite::Statement&, std::string, std::shared_ptr<T>);
                template<typename T, typename U>
                void bindPointersType(SQLite::Statement&, std::string, std::shared_ptr<T>, std::function<U(std::shared_ptr<T>)> const);
                template<typename T>
                void bindOptional(SQLite::Statement&, std::string, std::optional<T>);
        };

        template<typename T>
        void TableModifier::bindPointersTypeForId(SQLite::Statement& query, std::string bindName, std::shared_ptr<T> value)
        {
            if(value)
                query.bind(bindName, value->getId());
            else
                query.bind(bindName); // bind to null
        }
        template<typename T, typename U>
        void TableModifier::bindPointersType(
            SQLite::Statement& query, std::string bindName, std::shared_ptr<T> value, std::function<U(std::shared_ptr<T>)> const func)
        {
            if(value)
                query.bind(bindName, func(value));
            else
                query.bind(bindName); // bind to null
        }

        template<typename T>
        void TableModifier::bindOptional(SQLite::Statement& query, std::string bindName, std::optional<T> field)
        {
            if(field)
                query.bind(bindName, field.value());
            else
                query.bind(bindName); // bind to null
        }

    } // namespace Manager
} // namespace BookManager