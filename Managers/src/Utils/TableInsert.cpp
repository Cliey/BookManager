#include "Managers/Utils/TableInsert.hpp"
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
        bool TableInsert::addPerson(BookManager::Entity::Person personToAdd)
        {
            /*
                INSERT INTO table_name (field1, field2...., fieldN)
                VALUES (value1, value2...., valueN)
            */
            SQLite::Statement query(*database, "INSERT INTO Persons \
                (first_name, last_name, role) \
                VALUES (:first_name, :last_name, :role)");
            query.bind(":first_name", personToAdd.getFirstName());
            query.bind(":last_name", personToAdd.getLastName());
            query.bind(":role", static_cast<int>(personToAdd.getRole()));

            return query.exec() > 0;
        }

        bool TableInsert::addPublisher(BookManager::Entity::Publisher publisherToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Publishers (name) VALUES (:name)");
            query.bind(":name", publisherToAdd.getName());

            return query.exec() > 0;
        }

        bool TableInsert::addCategory(BookManager::Category::Category categoryToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Categories (name) VALUES (:name)");
            query.bind(":name", categoryToAdd.getName());

            return query.exec() > 0;
        }

        bool TableInsert::addBookSerie(BookManager::Entity::BookSerie bookSeriesToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO BookSeries (name) VALUES (:name)");
            query.bind(":name", bookSeriesToAdd.getName());

            return query.exec() > 0;
        }

        /************
         *  Not Yet *
         * *********/

        void TableInsert::bindOptionalDate(SQLite::Statement& query, std::string bindName, std::optional<time_t> date)
        {
            if(date)
                query.bind(bindName, convertDateToString(date.value())); // YYY-MM-DD
            else
                query.bind(bindName); // bind to null
        }

        std::string TableInsert::convertDateToString(std::time_t date)
        {
            std::tm* dateTm{localtime(&date)};
            char buffer [80];
            strftime (buffer,80,"%Y-%m-%d",dateTm);
            return std::string(buffer);
        }

        void TableInsert::addBooksPersonsTable(int bookId, std::vector<std::shared_ptr<Entity::Person>> persons)
        {
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
                        LOG_WINDOW("Error occured while adding authors : The author \"{}, {}\" doesn't exist.",
                            person->getLastName(), person->getFirstName())
                        throw;
                    }
                    LOG_WINDOW("Error occured while adding authors : {}", e.what())
                    throw;
                }
                catch(const std::exception& e)
                {
                    LOG_WINDOW("Error occured while adding authors : {}", e.what())
                    throw;
                }
            }
        }

        void TableInsert::addBooksSubCategoriesTable(int bookId, std::vector<std::shared_ptr<Category::Category>> subCategories)
        {
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
                        LOG_WINDOW("Error occured while adding Subcategories : The Subcategory \"{}\" doesn't exist.",
                            subCategorie->getName())
                        throw;
                    }
                    LOG_WINDOW("Error occured while adding Subcategories : {}", e.what());
                    throw;
                }
                catch(const std::exception& e)
                {
                    LOG_WINDOW("Error occured while adding Subcategories : {}", e.what())
                    throw;
                }
            }
        }

        void TableInsert::deleteInBooksSubCategoriesTable(int bookId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books_SubCategories WHERE bookId = :book_id");
            queryDelete.bind(":book_id", bookId);
            queryDelete.exec();
        }

        void TableInsert::deleteInBooksPersonsTable(int bookId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books_Persons WHERE bookId = :book_id");
            queryDelete.bind(":book_id", bookId);
            queryDelete.exec();
        }

        void TableInsert::deleteInBooksTable(int bookId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books WHERE id = :book_id");
            queryDelete.bind(":book_id", bookId);
            queryDelete.exec();
        }

        bool TableInsert::addBook(std::shared_ptr<BookManager::Book::Abstraction::Book> bookToAdd)
        {
            SQLite::Statement query(*database, "INSERT INTO Books \
                (   type, title, main_category, \
                    publisher, book_serie, published_date, \
                    purchased_date, price, status, is_read, \
                    start_reading_date, end_reading_date, rate) \
                VALUES( \
                    :type, :title, :main_category, \
                    :publisher, :book_serie, :published_date, \
                    :purchased_date, :price, :status, :is_read, \
                    :start_reading_date, :end_reading_date, :rate)");

            // Put this in InsertUpdateHelper (have to bind id in Update before call the Helper)
            query.bind(":type", static_cast<int>(bookToAdd->getType()));
            query.bind(":title", bookToAdd->title);
            bindPointersType<BookManager::Category::Category, const int>(
                query, ":main_category", bookToAdd->mainCategory, &BookManager::Category::Category::getId);
            bindPointersType<BookManager::Entity::Publisher, const int>(
                query, ":publisher", bookToAdd->publisher, &BookManager::Entity::Publisher::getId);
            bindPointersType<BookManager::Entity::BookSerie, const int>(
                query, ":book_serie", bookToAdd->bookSerie, &BookManager::Entity::BookSerie::getId);
            bindOptionalDate(query, ":published_date", bookToAdd->published);
            bindOptionalDate(query, ":purchased_date", bookToAdd->purchasedDate);
            if(bookToAdd->price)
                query.bind(":price", bookToAdd->price.value()); // YYY-MM-DD
            else
                query.bind(":price"); // bind to null

            query.bind(":status", static_cast<int>(bookToAdd->status));
            query.bind(":is_read", bookToAdd->isRead);
            bindOptionalDate(query, ":start_reading_date", bookToAdd->startReadingDate);
            bindOptionalDate(query, ":end_reading_date", bookToAdd->endReadingDate);
            query.bind(":rate", bookToAdd->rate);

            int lastIdBook;
            try
            {
                auto rowAdded = query.exec();
                lastIdBook = database->getLastInsertRowid();
                addBooksPersonsTable(lastIdBook, bookToAdd->author);
                addBooksSubCategoriesTable(lastIdBook, bookToAdd->subCategory);
                return rowAdded > 0;
            }
            catch(const std::exception& e)
            {
                deleteInBooksTable(lastIdBook);
                deleteInBooksPersonsTable(lastIdBook);
                deleteInBooksSubCategoriesTable(lastIdBook);
                LOG_ERROR("Error occured while adding Book : {}", e.what())
                return false;
            }
        }
    } // namespace Manager
} // namespace BookManager