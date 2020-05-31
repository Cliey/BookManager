#include "Managers/Utils/TableInsert.hpp"
#include "BookAbstract/Book.hpp"
#include "BookEnum/BookType.hpp"
#include "BookFactory/BookFactory.hpp"
#include "EntityTypes/BookSeries.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "Utils/EnumUtils.hpp"
#include "Utils/Log.hpp"
#include "Utils/Exceptions.hpp"
#include "../../../Category.hpp"
#include <iostream>
#include <sqlite3.h>

namespace BookManager
{
    namespace Manager
    {
        int TableInsert::getLastIdAddedInTable(const std::string table)
        {
            std::ostringstream stringStream;
            stringStream << "SELECT MAX(id) AS max_id FROM " << table;
            const std::string& tmp = stringStream.str();
            SQLite::Statement query(*database, tmp.c_str());
            query.executeStep();
            int maxId = query.getColumn("max_id");
            return maxId + 1;
        }

        std::tuple<bool, int> TableInsert::addPerson(BookManager::Entity::Person personToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Persons \
                (first_name, last_name, role) \
                VALUES (:first_name, :last_name, :role)");
            int lastId = getLastIdAddedInTable("Persons");

            return {tableModifier->modifyPersonTable(personToAdd, query), lastId};
        }

        std::tuple<bool, int> TableInsert::addPublisher(BookManager::Entity::Publisher publisherToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Publishers (name) VALUES (:name)");
            int lastId = getLastIdAddedInTable("Publishers");

            return {tableModifier->modifyPublisherTable(publisherToAdd, query), lastId};
        }

        std::tuple<bool, int> TableInsert::addCategory(BookManager::Category::Category categoryToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Categories (name) VALUES (:name)");
            int lastId = getLastIdAddedInTable("Categories");

            return {tableModifier->modifyCategoryTable(categoryToAdd, query), lastId};
        }


        std::tuple<bool, int> TableInsert::addBookSeries(BookManager::Entity::BookSeries bookSeriesToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO BookSeries (name) VALUES (:name)");
            int lastId = getLastIdAddedInTable("BookSeries");

            return {tableModifier->modifyBookSeriesTable(bookSeriesToAdd, query), lastId};
        }

        void TableInsert::addBooksPersonsTable(int bookId, std::vector<std::shared_ptr<Entity::Person>> persons)
        {
            SQLite::Statement queryInsert(*database, "INSERT INTO Books_Persons (bookId, personId) \
                VALUES (:book_id, :person_id)");
            try
            {
                tableModifier->modifyBooksPersonsTable(bookId, persons, queryInsert);
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }

        void TableInsert::addBooksSubCategoriesTable(int bookId, std::vector<std::shared_ptr<Category::Category>> subCategories)
        {
            SQLite::Statement queryInsert(*database, "INSERT INTO Books_SubCategories (bookId, subCategoryId) \
                VALUES (:book_id, :subCategory_id)");
            try
            {
                tableModifier->modifyBooksSubCategoriesTable(bookId, subCategories, queryInsert);
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }

        std::tuple<bool, int> TableInsert::addBook(std::shared_ptr<BookManager::Book::Abstraction::Book> bookToAdd)
        {
            SQLite::Transaction transaction(*database);
            SQLite::Statement query(*database, "INSERT INTO Books \
                (   type, title, main_category, \
                    publisher, book_serie, published_date, \
                    purchased_date, price, status, is_read, \
                    start_reading_date, end_reading_date, rate, comment) \
                VALUES( \
                    :type, :title, :main_category, \
                    :publisher, :book_serie, :published_date, \
                    :purchased_date, :price, :status, :is_read, \
                    :start_reading_date, :end_reading_date, :rate, :comment)");

            int lastIdBook;
            try
            {
                tableModifier->modifyBookTable(bookToAdd, query);
                lastIdBook = database->getLastInsertRowid();
                addBooksPersonsTable(lastIdBook, bookToAdd->generalInfo.author);
                addBooksSubCategoriesTable(lastIdBook, bookToAdd->categoryInfo.subCategory);
                transaction.commit();
                return {true, lastIdBook};
            }
            catch(const std::exception& e)
            {
                // Rollback
                LOG_ERROR("Error occurred while adding Book : {}", e.what())
                return {false, 0};
            }
        }
    } // namespace Manager
} // namespace BookManager