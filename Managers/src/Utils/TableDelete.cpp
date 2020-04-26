#include "Managers/Utils/TableDelete.hpp"
#include "Utils/Log.hpp"
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

        bool TableDelete::deleteInPersonTable(int personId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Persons WHERE id = :person_id");
            queryDelete.bind(":person_id", personId);
            return queryDelete.exec() > 0;
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
                    LOG_WINDOW_YES_NO(deletePerson, "Warning : the author has {} book(s) associated, are you sure you want to delete it?", count);
                    return returnValue;
                }
            }

            return deleteInPersonTable(personId);
        }

        bool TableDelete::deleteInPublisherTable(int publisherId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Publishers WHERE id = :publisher_id");
            queryDelete.bind(":publisher_id", publisherId);
            return queryDelete.exec() > 0;
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
                    LOG_WINDOW_YES_NO(deletePublisher, "Warning : the publisher has {} book(s) associated, are you sure you want to delete it?", count);
                    return returnValue;
                }
            }

            return deleteInPublisherTable(publisherId);
        }

        bool TableDelete::deleteInCategoryTable(int categoryId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Categories WHERE id = :category_id");
            queryDelete.bind(":category_id", categoryId);
            return queryDelete.exec() > 0;
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
                    auto deleteCategory = [this, categoryId, &returnValue]() { returnValue = this->deleteInBookSerieTable(categoryId); };
                    LOG_WINDOW_YES_NO(deleteCategory, "Warning : the category has {} book(s) associated, are you sure you want to delete it?", count);
                    return returnValue;
                }
            }

            return deleteInCategoryTable(categoryId);
        }

        bool TableDelete::deleteInBookSerieTable(int bookSerieId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM BookSeries WHERE id = :bookSerie_id");
            queryDelete.bind(":bookSerie_id", bookSerieId);
            return queryDelete.exec() > 0;
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
                    LOG_WINDOW_YES_NO(deleteBookSerie, "Warning : the book serie has {} book(s) associated, are you sure you want to delete it?", count);
                    return returnValue;
                }
            }

            return deleteInBookSerieTable(bookSerieId);
        }

        bool TableDelete::deleteInBooksTable(int bookId)
        {
            SQLite::Statement queryDelete(*database, "DELETE FROM Books WHERE id = :book_id");
            queryDelete.bind(":book_id", bookId);
            return queryDelete.exec() > 0;
        }
    } // namespace Manager
} // namespace BookManager