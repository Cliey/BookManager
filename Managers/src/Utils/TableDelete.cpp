#include "Managers/Utils/TableDelete.hpp"
#include "Utils/Log.hpp"
#include "Utils/Exceptions.hpp"
#include <iostream>
#include <sqlite3.h>

namespace BookManager
{
    namespace Manager
    {
        int countRelations(SQLite::Statement& queryCount)
        {
            int count = 0;
            while (queryCount.executeStep())
                count += queryCount.getColumn(0).getInt();
            return count;
        }

        std::string TableDelete::getName(SQLite::Statement& query, int id)
        {
            query.bind(":id", id);
            query.executeStep();
            return query.getColumn("name");
        }

        std::string TableDelete::getPersonName(int personId)
        {
            SQLite::Statement query(*database, "SELECT first_name, last_name FROM Persons WHERE id = :id");
            query.bind(":id", personId);
            query.executeStep();
            std::string firstName = query.getColumn("first_name");
            std::string lastName = query.getColumn("last_name");
            std::string returnStr = lastName + ", " + firstName;
            return returnStr;
        }

        bool TableDelete::deleteInTable(SQLite::Statement& queryDelete, int id)
        {
            queryDelete.bind(":id", id);
            return queryDelete.exec() > 0;
        }

        bool TableDelete::deleteInPersonTable(int personId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Persons WHERE id = :id");
            return deleteInTable(queryDelete, personId);
        }

        bool TableDelete::checkAndDeleteInPersonTable(int personId, bool bypassForeignKey)
        {
            SQLite::Statement queryCountBookWithAuthor(*database, "SELECT COUNT(*) FROM Books_Persons WHERE personId = :person_id");
            queryCountBookWithAuthor.bind(":person_id", personId);
            if(not bypassForeignKey)
            {
                if (int count = countRelations(queryCountBookWithAuthor); count > 0)
                {
                    bool returnValue = false;
                    auto deletePerson = [this, personId, &returnValue]() { returnValue = this->deleteInPersonTable(personId); };
                    std::string strException = "Warning : the author \"" + getPersonName(personId)  + "\" has " + std::to_string(count) + " book(s) associated, are you sure you want to delete it?";
                    LOG_ERROR(strException);
                    throw Utils::Exceptions::EC_ForeignKeyFound(strException, deletePerson);
                }
            }

            return deleteInPersonTable(personId);
        }

        bool TableDelete::deleteInPublisherTable(int publisherId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Publishers WHERE id = :id");
            return deleteInTable(queryDelete, publisherId);
        }

        bool TableDelete::checkAndDeleteInPublisherTable(int publisherId, bool bypassForeignKey)
        {
            SQLite::Statement queryCountBookWithPublisher(*database, "SELECT COUNT(*) FROM Books WHERE publisher = :publisher_id");
            queryCountBookWithPublisher.bind(":publisher_id", publisherId);
            if(not bypassForeignKey)
            {
                if (int count = countRelations(queryCountBookWithPublisher); count > 0)
                {
                    bool returnValue = false;
                    auto deletePublisher = [this, publisherId, &returnValue]() { returnValue = this->deleteInPublisherTable(publisherId); };
                    SQLite::Statement queryGetCategoryName(*database, "SELECT name FROM Publishers WHERE id = :id");
                    std::string strException = "Warning : the publisher \"" + getName(queryGetCategoryName, publisherId) + "\" has " + std::to_string(count) + " book(s) associated, are you sure you want to delete it?";
                    LOG_ERROR(strException);
                    throw Utils::Exceptions::EC_ForeignKeyFound(strException, deletePublisher);
                }
            }

            return deleteInPublisherTable(publisherId);
        }

        bool TableDelete::deleteInCategoryTable(int categoryId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Categories WHERE id = :id");
            return deleteInTable(queryDelete, categoryId);
        }

        bool TableDelete::checkAndDeleteInCategoryTable(int categoryId, bool bypassForeignKey)
        {
            SQLite::Statement queryCountBookWithMainCategory(*database, "SELECT COUNT(*) FROM Books WHERE main_category = :category_id");
            queryCountBookWithMainCategory.bind(":category_id", categoryId);
            SQLite::Statement queryCountBookWithSubCategory(*database, "SELECT COUNT(*) FROM Books_SubCategories WHERE subCategoryId = :subCategory_id");
            queryCountBookWithSubCategory.bind(":subCategory_id", categoryId);
            if(not bypassForeignKey)
            {
                if (int count = countRelations(queryCountBookWithMainCategory) + countRelations(queryCountBookWithSubCategory); count > 0)
                {
                    bool returnValue = false;
                    auto deleteCategory = [this, categoryId, &returnValue]() { returnValue = this->deleteInCategoryTable(categoryId); };
                    SQLite::Statement queryGetCategoryName(*database, "SELECT name FROM Categories WHERE id = :id");

                    std::string strException = "Warning : the category \"" + getName(queryGetCategoryName, categoryId) + "\" has " + std::to_string(count) + " book(s) associated, are you sure you want to delete it?";
                    LOG_ERROR(strException);
                    throw Utils::Exceptions::EC_ForeignKeyFound(strException, deleteCategory);
                }
            }

            return deleteInCategoryTable(categoryId);
        }

        bool TableDelete::deleteInBookSerieTable(int bookSerieId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM BookSeries WHERE id = :id");
            return deleteInTable(queryDelete, bookSerieId);
        }

        bool TableDelete::checkAndDeleteInBookSerieTable(int bookSerieId, bool bypassForeignKey)
        {
            SQLite::Statement queryCountBookWithBookSerie(*database, "SELECT COUNT(*) FROM Books WHERE book_serie = :bookSerie_id");
            queryCountBookWithBookSerie.bind(":bookSerie_id", bookSerieId);
            if(not bypassForeignKey)
            {
                if (int count = countRelations(queryCountBookWithBookSerie); count > 0)
                {
                    bool returnValue = false;
                    auto deleteBookSerie = [this, bookSerieId, &returnValue]() { returnValue = this->deleteInBookSerieTable(bookSerieId); };
                    SQLite::Statement queryGetBookSerieName(*database, "SELECT name FROM BookSeries WHERE id = :id");
                    std::string strException = "Warning : the book serie \"" + getName(queryGetBookSerieName, bookSerieId) + "\" has " + std::to_string(count) + " book(s) associated, are you sure you want to delete it?";
                    LOG_ERROR(strException);
                    throw Utils::Exceptions::EC_ForeignKeyFound(strException, deleteBookSerie);
                }
            }

            return deleteInBookSerieTable(bookSerieId);
        }

        bool TableDelete::deleteInBooksTable(int bookId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books WHERE id = :id");
            return deleteInTable(queryDelete, bookId);
        }
    } // namespace Manager
} // namespace BookManager