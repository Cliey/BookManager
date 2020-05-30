#pragma once
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <string>
#include <ctime>
#include <functional>
#include <iostream>

namespace BookManager
{
    namespace Entity
    {
        class BookSeries;
        class Person;
        class Publisher;
        enum class Role;
    }
    namespace Category
    {
        class Category;
    }
    namespace Book
	{
        enum class BookType;
        enum class BookStatus;
        namespace Abstraction
        {
            class Book;
        }
    }

    namespace Manager
    {
        class TableDeserializers
        {
            public:
                TableDeserializers(std::shared_ptr<SQLite::Database> database) : database(database) {}
                std::vector<BookManager::Entity::Person> deserializePersonTable(int limit, int offset);
                std::vector<BookManager::Entity::Person> deserializePersonTable(int limit, int offset, BookManager::Entity::Role role);
                std::vector<BookManager::Entity::Publisher> deserializePublisherTable(int limit, int offset);
                std::vector<BookManager::Category::Category> deserializeCategoryTable(int limit, int offset);
                std::vector<BookManager::Entity::BookSeries> deserializeBookSeriesTable(int limit, int offset);
                std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializeBookTable(int limit, int offset);

                template<typename T>
                T deserializeOneElementSimpleTableIdAndName(SQLite::Statement&);

                BookManager::Entity::Person deserializeOnePerson(SQLite::Statement&);

            private:
                std::vector<BookManager::Entity::Person> executePersonTableQuery(SQLite::Statement& query);
                BookManager::Book::BookType getType(int type);
                BookManager::Book::BookStatus getBookStatus(int status);
                std::time_t convertDate(std::string);
                std::string getElementOfDateAndEraseIt(std::string& date);
                template<typename T>
                std::shared_ptr<T> setIfColumnNotNull(SQLite::Statement& query, std::string columnName, std::function<T(TableDeserializers, int)> func);
                template<typename T>
                void setOptionalFieldIfExist(std::optional<T>& fieldToInit, SQLite::Statement& query, std::string column);

                BookManager::Category::Category getCategoryFromId(int);
                BookManager::Entity::BookSeries getBookSeriesFromId(int);
                BookManager::Entity::Publisher getPublisherFromId(int);
                BookManager::Entity::Person getAuthorFromId(int);
                std::vector<std::shared_ptr<Category::Category>> getSubcategory(int);
                std::vector<std::shared_ptr<BookManager::Entity::Person>> getAuthors(int);

                std::shared_ptr<SQLite::Database> database;
        };

        template<typename T>
        T TableDeserializers::deserializeOneElementSimpleTableIdAndName(SQLite::Statement& query)
        {
            int id = query.getColumn("id");
            std::string name = query.getColumn("name");
            return T{id, name};
        }

        template<typename T>
        std::shared_ptr<T> TableDeserializers::setIfColumnNotNull(SQLite::Statement& query, std::string columnName, std::function<T(TableDeserializers, int)> func)
        {
            auto columnChar = columnName.c_str();
            if(!query.isColumnNull(columnChar))
            {
                int field = query.getColumn(columnChar);
                return std::make_shared<T>(func(*this, field));
            }
            return nullptr;
        }

        template<typename T>
        void TableDeserializers::setOptionalFieldIfExist(std::optional<T>& fieldToInit, SQLite::Statement& query, std::string column)
        {
            if(query.isColumnNull(column.c_str()))
                return;

            auto field = query.getColumn(column.c_str());
            fieldToInit = std::make_optional<double>(field);
        }
    } // namespace Manager
} // namespace BookManager