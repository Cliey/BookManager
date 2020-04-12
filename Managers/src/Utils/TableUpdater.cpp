#include "Managers/Utils/TableUpdater.hpp"
#include "BookAbstract/Book.hpp"
#include "BookEnum/BookType.hpp"
#include "BookFactory/BookFactory.hpp"
#include "EntityTypes/BookSerie.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "Utils/EnumUtils.hpp"
#include "Utils/Log.hpp"
#include "../../../Category.hpp"
#include <iostream>

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
    } // namespace Manager
} // namespace BookManager