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
        bool TableInsert::addPerson(BookManager::Entity::Person personToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Persons \
                (first_name, last_name, role) \
                VALUES (:first_name, :last_name, :role)");

            return tableModifier->modifyPersonTable(personToAdd, query);
        }

        bool TableInsert::addPublisher(BookManager::Entity::Publisher publisherToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Publishers (name) VALUES (:name)");

            return tableModifier->modifyPublisherTable(publisherToAdd, query);
        }

        bool TableInsert::addCategory(BookManager::Category::Category categoryToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Categories (name) VALUES (:name)");

            return tableModifier->modifyCategoryTable(categoryToAdd, query);
        }

        bool TableInsert::addBookSeries(BookManager::Entity::BookSeries bookSeriesToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO BookSeries (name) VALUES (:name)");

            return tableModifier->modifyBookSeriesTable(bookSeriesToAdd, query);
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

        bool TableInsert::addBook(std::shared_ptr<BookManager::Book::Abstraction::Book> bookToAdd)
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
                return true;
            }
            catch(const std::exception& e)
            {
                // Rollback
                LOG_ERROR("Error occured while adding Book : {}", e.what())
                return false;
            }
        }
    } // namespace Manager
} // namespace BookManager