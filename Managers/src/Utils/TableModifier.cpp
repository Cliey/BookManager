#include "Managers/Utils/TableModifier.hpp"
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
        bool TableModifier::modifyPersonTable(BookManager::Entity::Person person, SQLite::Statement& query)
        {
            query.bind(":first_name", person.getFirstName());
            query.bind(":last_name", person.getLastName());
            query.bind(":role", static_cast<int>(person.getRole()));

            return query.exec() > 0;
        }

        bool TableModifier::modifyPublisherTable(BookManager::Entity::Publisher publisher, SQLite::Statement& query)
        {
            query.bind(":name", publisher.getName());

            return query.exec() > 0;
        }

        bool TableModifier::modifyCategoryTable(BookManager::Category::Category category, SQLite::Statement& query)
        {
            query.bind(":name", category.getName());

            return query.exec() > 0;
        }

        bool TableModifier::modifyBookSeriesTable(BookManager::Entity::BookSeries bookSeries, SQLite::Statement& query)
        {
            query.bind(":name", bookSeries.getName());

            return query.exec() > 0;
        }

        template<>
        void TableModifier::bindOptional<time_t>(SQLite::Statement& query, std::string bindName, std::optional<time_t> date)
        {
            if(date)
                query.bind(bindName, convertDateToString(date.value())); // YYY-MM-DD
            else
                query.bind(bindName); // bind to null
        }

        std::string TableModifier::convertDateToString(std::time_t date)
        {
            std::tm* dateTm{localtime(&date)};
            char buffer [80];
            strftime (buffer,80,"%Y-%m-%d",dateTm);
            return std::string(buffer);
        }

        void TableModifier::modifyBooksPersonsTable(int bookId, std::vector<std::shared_ptr<Entity::Person>> persons, SQLite::Statement& query)
        {
            for(auto person : persons)
            {
                try
                {
                    query.bind(":book_id", bookId);
                    query.bind(":person_id", person->getId());
                    query.exec();
                    query.reset();
                }
                catch (const SQLite::Exception &e) {
                    if (e.getExtendedErrorCode() == SQLITE_CONSTRAINT_FOREIGNKEY)
                    {
                        LOG_WINDOW("Error occurred with author : The author \"{}, {}\" doesn't exist.",
                            person->getLastName(), person->getFirstName())
                        throw;
                    }
                    LOG_WINDOW("Error occurred with author : {}", e.what())
                    throw;
                }
                catch(const std::exception& e)
                {
                    LOG_WINDOW("Error occurred with author : {}", e.what())
                    throw;
                }
            }
        }

        void TableModifier::modifyBooksSubCategoriesTable(int bookId, std::vector<std::shared_ptr<Category::Category>> subCategories, SQLite::Statement& query)
        {
            for(auto subCategorie : subCategories)
            {
                try
                {
                    query.bind(":book_id", bookId);
                    query.bind(":subCategory_id", subCategorie->getId());
                    query.exec();
                    query.reset();
                }
                catch (const SQLite::Exception &e) {
                    if (e.getExtendedErrorCode() == SQLITE_CONSTRAINT_FOREIGNKEY)
                    {
                        LOG_WINDOW("Error occurred with Subcategories : The Subcategory \"{}\" doesn't exist.",
                            subCategorie->getName())
                        throw;
                    }
                    LOG_WINDOW("Error occurred with Subcategories : {}", e.what());
                    throw;
                }
                catch(const std::exception& e)
                {
                    LOG_WINDOW("Error occurred with Subcategories : {}", e.what())
                    throw;
                }
            }
        }

        void TableModifier::deleteInTableWithBookIdBind(int bookId, SQLite::Statement& query)
        {
            query.bind(":book_id", bookId);
            query.exec();
        }

        void TableModifier::bindString(SQLite::Statement& query, std::string bindName, std::string field)
        {
            if(!field.empty())
                query.bind(bindName, field);
            else
                query.bind(bindName); // bind to null
        }

        int TableModifier::modifyBookTable(std::shared_ptr<BookManager::Book::Abstraction::Book> book, SQLite::Statement& query)
        {
            query.bind(":type", static_cast<int>(book->getType()));
            query.bind(":title", book->generalInfo.title);
            bindPointersType<BookManager::Category::Category, const int>(
                query, ":main_category", book->categoryInfo.mainCategory, &BookManager::Category::Category::getId);
            bindPointersType<BookManager::Entity::Publisher, const int>(
                query, ":publisher", book->generalInfo.publisher, &BookManager::Entity::Publisher::getId);
            bindPointersType<BookManager::Entity::BookSeries, const int>(
                query, ":book_serie", book->generalInfo.bookSeries, &BookManager::Entity::BookSeries::getId);
            bindOptional<time_t>(query, ":published_date", book->generalInfo.published);
            bindOptional<time_t>(query, ":purchased_date", book->statInfo.purchasedDate);
            bindOptional<double>(query, ":price", book->statInfo.price);
            bindOptional<time_t>(query, ":start_reading_date", book->statInfo.startReadingDate);
            bindOptional<time_t>(query, ":end_reading_date", book->statInfo.endReadingDate);

            query.bind(":status", static_cast<int>(book->additionalInfo.status));
            query.bind(":is_read", book->additionalInfo.isRead);
            bindOptional<int>(query, ":rate", book->additionalInfo.rate);
            bindString(query, ":comment", book->additionalInfo.comment);

            try
            {
                auto rowModified = query.exec();
                return rowModified;
            }
            catch(const std::exception& e)
            {
                throw;
            }
        }
    } // namespace Manager
} // namespace BookManager