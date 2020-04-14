#include "Managers/Utils/TableUpdater.hpp"
#include "BookAbstract/Book.hpp"
#include "BookEnum/BookType.hpp"
#include "BookFactory/BookFactory.hpp"
#include "EntityTypes/BookSerie.hpp"
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
        bool TableUpdater::updatePerson(BookManager::Entity::Person personToUpdate)
        {
            /*
                UPDATE table_name
                SET column1 = value1, column2 = value2...., columnN = valueN
                WHERE [condition];
            */
            SQLite::Statement query(*database, "UPDATE Persons \
                SET first_name = :first_name, last_name = :last_name, role = :role \
                WHERE id = :id");
            query.bind(":first_name", personToUpdate.getFirstName());
            query.bind(":last_name", personToUpdate.getLastName());
            query.bind(":role", static_cast<int>(personToUpdate.getRole()));
            query.bind(":id", personToUpdate.getId());

            return query.exec() > 0;
        }

        bool TableUpdater::updatePublisher(BookManager::Entity::Publisher publisherToUpdate)
        {
            SQLite::Statement query(*database, "UPDATE Publishers \
                SET name = :name \
                WHERE id = :id");
            query.bind(":name", publisherToUpdate.getName());
            query.bind(":id", publisherToUpdate.getId());

            return query.exec() > 0;
        }

        bool TableUpdater::updateCategory(BookManager::Category::Category categoryToUpdate)
        {
            SQLite::Statement query(*database, "UPDATE Categories \
                SET name = :name \
                WHERE id = :id");
            query.bind(":name", categoryToUpdate.getName());
            query.bind(":id", categoryToUpdate.getId());

            return query.exec() > 0;
        }

        bool TableUpdater::updateBookSerie(BookManager::Entity::BookSerie bookSeriesToUpdate)
        {
            SQLite::Statement query(*database, "UPDATE BookSeries \
                SET name = :name \
                WHERE id = :id");
            query.bind(":name", bookSeriesToUpdate.getName());
            query.bind(":id", bookSeriesToUpdate.getId());

            return query.exec() > 0;
        }


        void TableUpdater::bindOptionalDate(SQLite::Statement& query, std::string bindName, std::optional<time_t> date)
        {
            if(date)
                query.bind(bindName, convertDateToString(date.value())); // YYY-MM-DD
            else
                query.bind(bindName); // bind to null
        }

        std::string TableUpdater::convertDateToString(std::time_t date)
        {
            std::tm* dateTm{localtime(&date)};
            char buffer [80];
            strftime (buffer,80,"%Y-%m-%d",dateTm);
            return std::string(buffer);
        }

        void TableUpdater::updateBooksPersonsTable(int bookId, std::vector<std::shared_ptr<Entity::Person>> persons)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books_Persons WHERE bookId = :book_id");
            queryDelete.bind(":book_id", bookId);
            queryDelete.exec();
            SQLite::Statement queryInsert(*database, "INSERT INTO Books_Persons (bookId, personId) \
                VALUES (:book_id, :person_id)");
            for(auto person : persons)
            {
                try
                {
                    queryInsert.bind(":book_id", bookId);
                    queryInsert.bind(":person_id", person->getId());
                    queryInsert.exec();
                    queryInsert.reset();
                }
                catch (const SQLite::Exception &e) {
                    if (e.getExtendedErrorCode() == SQLITE_CONSTRAINT_FOREIGNKEY)
                    {
                        LOG_WINDOW("Error occured while updating authors : The author \"{}, {}\" doesn't exist.",
                            person->getLastName(), person->getFirstName())
                        throw;
                    }
                    LOG_WINDOW("Error occured while updating authors : {}", e.what())
                    throw;
                }
                catch(const std::exception& e)
                {
                    LOG_WINDOW("Error occured while updating authors : {}", e.what())
                    throw;
                }
            }
        }

        void TableUpdater::updateBooksSubCategoriesTable(int bookId, std::vector<std::shared_ptr<Category::Category>> subCategories)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books_SubCategories WHERE bookId = :book_id");
            queryDelete.bind(":book_id", bookId);
            queryDelete.exec();
            SQLite::Statement queryInsert(*database, "INSERT INTO Books_SubCategories (bookId, subCategoryId) \
                VALUES (:book_id, :subCategory_id)");
            for(auto subCategorie : subCategories)
            {
                try
                {
                    queryInsert.bind(":book_id", bookId);
                    queryInsert.bind(":subCategory_id", subCategorie->getId());
                    queryInsert.exec();
                    queryInsert.reset();
                }
                catch (const SQLite::Exception &e) {
                    if (e.getExtendedErrorCode() == SQLITE_CONSTRAINT_FOREIGNKEY)
                    {
                        LOG_WINDOW("Error occured while updating Subcategories : The Subcategory \"{}\" doesn't exist.",
                            subCategorie->getName())
                        throw;
                    }
                    LOG_WINDOW("Error occured while updating Subcategories : {}", e.what());
                    throw;
                }
                catch(const std::exception& e)
                {
                    LOG_WINDOW("Error occured while updating Subcategories : {}", e.what())
                    throw;
                }
            }
        }

        bool TableUpdater::updateBook(std::shared_ptr<BookManager::Book::Abstraction::Book> bookToUpdate)
        {
            // Update Book -> simple
            SQLite::Statement query(*database, "UPDATE Books \
                SET type = :type, title = :title, main_category = :main_category, \
                    publisher = :publisher, book_serie = :book_serie, published_date = :published_date, \
                    purchased_date = :purchased_date, price = :price, status = :status, is_read = :is_read, \
                    start_reading_date = :start_reading_date, end_reading_date = :end_reading_date, rate = :rate \
                WHERE id = :id");
            query.bind(":id", bookToUpdate->id);
            query.bind(":type", static_cast<int>(bookToUpdate->getType()));
            query.bind(":title", bookToUpdate->title);
            bindPointersType<BookManager::Category::Category, const int>(
                query, ":main_category", bookToUpdate->mainCategory, &BookManager::Category::Category::getId);
            bindPointersType<BookManager::Entity::Publisher, const int>(
                query, ":publisher", bookToUpdate->publisher, &BookManager::Entity::Publisher::getId);
            bindPointersType<BookManager::Entity::BookSerie, const int>(
                query, ":book_serie", bookToUpdate->bookSerie, &BookManager::Entity::BookSerie::getId);
            bindOptionalDate(query, ":published_date", bookToUpdate->published);
            bindOptionalDate(query, ":purchased_date", bookToUpdate->purchasedDate);
            if(bookToUpdate->price)
                query.bind(":price", bookToUpdate->price.value()); // YYY-MM-DD
            else
                query.bind(":price"); // bind to null

            query.bind(":status", static_cast<int>(bookToUpdate->status));
            query.bind(":is_read", bookToUpdate->isRead);
            bindOptionalDate(query, ":start_reading_date", bookToUpdate->startReadingDate);
            bindOptionalDate(query, ":end_reading_date", bookToUpdate->endReadingDate);
            query.bind(":rate", bookToUpdate->rate);

            try
            {
                // If error : lost BooksPerson & BooksSubCategories. Should undo modification : transaction ?
                updateBooksPersonsTable(bookToUpdate->id, bookToUpdate->author);
                updateBooksSubCategoriesTable(bookToUpdate->id, bookToUpdate->subCategory);
                return query.exec() > 0;
            }
            catch(const std::exception& e)
            {
                LOG_ERROR("Error occured while adding Book : {}", e.what())
                return false;
            }
        }
    } // namespace Manager
} // namespace BookManager