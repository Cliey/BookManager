#pragma once
#include <memory>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
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
        namespace Abstraction
        {
            class Book;
        }
    }

    namespace Manager
    {

        class TableDeserializers;
        class TableDelete;
        class TableInsert;
        class TableUpdater;
        class DatabaseManager
        {
        public:
            DatabaseManager(std::string databaseName);
            ~DatabaseManager();

            std::vector<BookManager::Entity::Person> getPersonVector(int limit, int offset);
            std::vector<BookManager::Entity::Person> getPersonVector(int limit, int offset, BookManager::Entity::Role role);
            std::vector<BookManager::Entity::Publisher> getPublisherVector(int limit, int offset);
            std::vector<BookManager::Category::Category> getCategoryVector(int limit, int offset);
            std::vector<BookManager::Entity::BookSeries> getBookSeriesVector(int limit, int offset);
            std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> getBookVector(int limit, int offset);

            bool updatePerson(BookManager::Entity::Person);
            bool updatePublisher(BookManager::Entity::Publisher);
            bool updateCategory(BookManager::Category::Category);
            bool updateBookSeries(BookManager::Entity::BookSeries);
            bool updateBook(std::shared_ptr<BookManager::Book::Abstraction::Book>);

            std::tuple<bool, int> insertPerson(BookManager::Entity::Person);
            std::tuple<bool, int> insertPublisher(BookManager::Entity::Publisher);
            std::tuple<bool, int> insertCategory(BookManager::Category::Category);
            std::tuple<bool, int> insertBookSeries(BookManager::Entity::BookSeries);
            std::tuple<bool, int> insertBook(std::shared_ptr<BookManager::Book::Abstraction::Book>);

            bool deletePerson(int, bool);
            bool deletePublisher(int, bool);
            bool deleteCategory(int, bool);
            bool deleteBookSeries(int, bool);
            bool deleteBook(int);
            // shared_ptr<DatabaseGetter> getPerson(); // DatabaseGetter.byId(int)
            // PersonDatabaseGetter getPerson(); // DatabaseGetter.byName(string)
            // Person getPersonById(); // DatabaseGetter.byId(int)


        private:
            void loadDatabase(SQLite::Database& database);
            void createDatabase();
            void initTableActionObject();

            std::string databasePath;

            std::unique_ptr<TableDeserializers> createTableDeserializer(std::shared_ptr<SQLite::Database>);
            std::unique_ptr<TableInsert> createTableInsert(std::shared_ptr<SQLite::Database>);
            std::unique_ptr<TableUpdater> createTableUpdater(std::shared_ptr<SQLite::Database>);
            std::unique_ptr<TableDelete> createTableDelete(std::shared_ptr<SQLite::Database>);

            std::unique_ptr<TableDeserializers> tableDeserializer;
            std::unique_ptr<TableDelete> tableDelete;
            std::unique_ptr<TableInsert> tableInsert;
            std::unique_ptr<TableUpdater> tableUpdater;
            std::shared_ptr<SQLite::Database> database;
        };

    } // namespace Manager
} // namespace BookManager
