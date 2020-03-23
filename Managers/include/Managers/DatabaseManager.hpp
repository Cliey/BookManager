#pragma once
#include <memory>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

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

        class TableDeserializers;
        class DatabaseManager
        {
        public:
            static std::shared_ptr<DatabaseManager> getDbManager();

            std::vector<BookManager::Entity::Person> getPersonVector(int limit, int offset);
            std::vector<BookManager::Entity::Publisher> getPublisherVector(int limit, int offset);
            std::vector<BookManager::Category::Category> getCategoryVector(int limit, int offset);
            std::vector<BookManager::Entity::BookSerie> getBookSerieVector(int limit, int offset);
            std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> getBookVector(int limit, int offset);

            void insertPerson(BookManager::Entity::Person);
            void insertPublisher(BookManager::Entity::Publisher);
            void insertCategory(BookManager::Category::Category);
            void insertBookSerie(BookManager::Entity::BookSerie);
            // void insertBook();

            // shared_ptr<DatabaseGetter> getPerson(); // DatabaseGetter.byId(int)
            // PersonDatabaseGetter getPerson(); // DatabaseGetter.byName(string)
            // Person getPersonById(); // DatabaseGetter.byId(int)


        private:
            DatabaseManager();
            void loadDatabase(SQLite::Database& database);
            void createDatabase();

            std::unique_ptr<TableDeserializers> createTableDeserializer(std::shared_ptr<SQLite::Database> database);

            std::unique_ptr<TableDeserializers> tableDeserializer;
            std::shared_ptr<SQLite::Database> database;
        };

    } // namespace Manager
} // namespace BookManager
