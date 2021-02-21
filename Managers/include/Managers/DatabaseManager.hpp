#pragma once
#include <memory>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
#include "Managers/Utils/QueryBuilder.hpp"
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
        namespace Abstraction
        {
            class Book;
        }
    }

    namespace Manager
    {
        namespace SqlOperator
        {
            class InterfaceOperator;
        }

        class TableDeserializers;
        class TableDelete;
        class TableInsert;
        class TableUpdater;
        class DatabaseManager
        {
        public:
            struct SearchOption
            {
                std::string tableName;
                std::shared_ptr<SqlOperator::InterfaceOperator> where;
                int limit;
                int offset;
                std::string orderBy;
                QueryBuilder::Order order = QueryBuilder::Order::ASCENDANT;
            };

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

            // template<class T>
            // std::vector<T> search(int object, int limit, int offset);
            // template<class T>
            // void search(std::vector<T> returnValue, int object, int limit, int offset);

            std::vector<BookManager::Entity::Person> searchPerson(const SearchOption&);
            std::vector<BookManager::Entity::Publisher> searchPublisher(const SearchOption&);
            std::vector<BookManager::Category::Category> searchCategory(const SearchOption&);
            std::vector<BookManager::Entity::BookSeries> searchBookSeries(const SearchOption&);
            std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> searchBook(const SearchOption&);

        private:
            void loadDatabase(SQLite::Database& database);
            void createDatabase();
            void initTableActionObject();

            std::string databasePath;

            std::unique_ptr<TableDeserializers> createTableDeserializer(std::shared_ptr<SQLite::Database>);
            std::unique_ptr<TableInsert> createTableInsert(std::shared_ptr<SQLite::Database>);
            std::unique_ptr<TableUpdater> createTableUpdater(std::shared_ptr<SQLite::Database>);
            std::unique_ptr<TableDelete> createTableDelete(std::shared_ptr<SQLite::Database>);

            SQLite::Statement buildQuery(const SearchOption&);
            SQLite::Statement buildQuery(const std::string&, const SearchOption&);

            std::unique_ptr<TableDeserializers> tableDeserializer;
            std::unique_ptr<TableDelete> tableDelete;
            std::unique_ptr<TableInsert> tableInsert;
            std::unique_ptr<TableUpdater> tableUpdater;
            std::shared_ptr<SQLite::Database> database;
        };

        // template<class T>
        // std::vector<T> DatabaseManager::search(int object, int limit, int offset)
        // {
        //     QueryBuilder queryBuilder;
        //     std::string queryStr;
        //     std::vector<T> returnValue;
        //     switch(object)
        //     {
        //         case 0:
        //             {
        //                 queryBuilder.reset();
        //                 queryStr = queryBuilder.selectFrom("Persons").limit(limit).offset(offset).getQuery();
        //                 std::cout << "query str = " << queryStr << std::endl;
        //                 SQLite::Statement queryPerson(*database, queryStr);
        //                 return executePersonQuery(queryPerson);
        //             }
        //             break;
        //         case 1:
        //             {
        //                 queryBuilder.reset();
        //                 queryStr = queryBuilder.selectFrom("Persons").limit(limit).offset(offset).getQuery();
        //                 SQLite::Statement queryPublisher(*database, queryStr);
        //                 return std::vector<T>();
        //             }
        //             break;

        //         default:
        //             return std::vector<T>();
        //     }
        // }

        // template<class T>
        // void DatabaseManager::search(std::vector<T> returnValue, int object, int limit, int offset)
        // {
        //     QueryBuilder queryBuilder;
        //     std::string queryStr;
        //     switch(object)
        //     {
        //         case 0:
        //             {
        //                 queryBuilder.reset();
        //                 queryStr = queryBuilder.selectFrom("Persons").limit(limit).offset(offset).getQuery();
        //                 std::cout << "query str = " << queryStr << std::endl;
        //                 SQLite::Statement queryPerson(*database, queryStr);
        //                 returnValue = executePersonQuery(queryPerson);
        //             }
        //             break;
        //         case 1:
        //             {
        //                 queryBuilder.reset();
        //                 queryStr = queryBuilder.selectFrom("Persons").limit(limit).offset(offset).getQuery();
        //                 SQLite::Statement queryPublisher(*database, queryStr);
        //                 returnValue = executePublisherQuery(queryPublisher);
        //             }
        //             break;

        //         default:
        //             returnValue = std::vector<T>();
        //     }
        // }


    } // namespace Manager
} // namespace BookManager
