#include "Managers/Utils/TableUpdater.hpp"
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
        SQLite::Statement TableUpdater::createQueryAndBindId(std::string queryStr, int idToBind)
        {
            SQLite::Statement query(*database, queryStr);
            query.bind(":id", idToBind);
            return query;
        }

        bool TableUpdater::updatePerson(BookManager::Entity::Person personToUpdate)
        {
            /*
                UPDATE table_name
                SET column1 = value1, column2 = value2...., columnN = valueN
                WHERE [condition];
            */
            SQLite::Statement query = createQueryAndBindId(
                "UPDATE Persons \
                    SET first_name = :first_name, last_name = :last_name, role = :role \
                    WHERE id = :id",
                personToUpdate.getId());

            return tableModifier->modifyPersonTable(personToUpdate, query);
        }

        bool TableUpdater::updatePublisher(BookManager::Entity::Publisher publisherToUpdate)
        {
            SQLite::Statement query = createQueryAndBindId(
                "UPDATE Publishers \
                    SET name = :name \
                    WHERE id = :id",
                publisherToUpdate.getId());

            return tableModifier->modifyPublisherTable(publisherToUpdate, query);
        }

        bool TableUpdater::updateCategory(BookManager::Category::Category categoryToUpdate)
        {
            SQLite::Statement query = createQueryAndBindId(
                "UPDATE Categories \
                    SET name = :name \
                    WHERE id = :id", categoryToUpdate.getId());

            return tableModifier->modifyCategoryTable(categoryToUpdate, query);
        }

        bool TableUpdater::updateBookSeries(BookManager::Entity::BookSeries bookSeriesToUpdate)
        {
            SQLite::Statement query = createQueryAndBindId(
                "UPDATE BookSeries \
                    SET name = :name \
                    WHERE id = :id",
                bookSeriesToUpdate.getId());

            return tableModifier->modifyBookSeriesTable(bookSeriesToUpdate, query);
        }

        void TableUpdater::updateBooksPersonsTable(int bookId, std::vector<std::shared_ptr<Entity::Person>> persons)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books_Persons WHERE bookId = :book_id");
            tableModifier->deleteInTableWithBookIdBind(bookId, queryDelete);
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

        void TableUpdater::updateBooksSubCategoriesTable(int bookId, std::vector<std::shared_ptr<Category::Category>> subCategories)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books_SubCategories WHERE bookId = :book_id");
            tableModifier->deleteInTableWithBookIdBind(bookId, queryDelete);
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

        bool TableUpdater::updateBook(std::shared_ptr<BookManager::Book::Abstraction::Book> bookToUpdate)
        {
            SQLite::Transaction transaction(*database);
            SQLite::Statement query = createQueryAndBindId(
                "UPDATE Books \
                SET type = :type, title = :title, main_category = :main_category, \
                    publisher = :publisher, book_serie = :book_serie, published_date = :published_date, \
                    purchased_date = :purchased_date, price = :price, status = :status, is_read = :is_read, \
                    start_reading_date = :start_reading_date, end_reading_date = :end_reading_date, rate = :rate, \
                    comment = :comment \
                WHERE id = :id",  bookToUpdate->id);

            try
            {
                if(tableModifier->modifyBookTable(bookToUpdate, query) == 0)
                {
                    LOG_ERROR("Error occurred while updating Book : Id is not associated to any book")
                    return false;
                }
                updateBooksPersonsTable(bookToUpdate->id, bookToUpdate->generalInfo.author);
                updateBooksSubCategoriesTable(bookToUpdate->id, bookToUpdate->categoryInfo.subCategory);
                transaction.commit();
                return  true;
            }
            catch(const std::exception& e)
            {
                // Rollback
                LOG_ERROR("Error occurred while updating Book : {}", e.what())
                return false;
            }
        }
    } // namespace Manager
} // namespace BookManager