#include "Managers/Utils/TableDeserializers.hpp"
#include "BookAbstract/Book.hpp"
#include "BookEnum/BookType.hpp"
#include "BookFactory/BookFactory.hpp"
#include "EntityTypes/BookSerie.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "Utils/EnumUtils.hpp"
#include "Utils/Log.hpp"
#include "../../../Category.hpp"

namespace BookManager
{
    namespace Manager
    {
        std::vector<BookManager::Entity::Person> TableDeserializers::deserializePersonTable(int limit, int offset)
        {
            std::vector<BookManager::Entity::Person> personVector;
            SQLite::Statement query(*database, "SELECT * FROM Persons LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                personVector.emplace_back(deserializeOnePerson(query));
            }

            for(auto person : personVector)
            {
                LOG_INFO("Person : ({}) {} {} is a(n) {}",
                    person.getId(), person.getFirstName(), person.getLastName(), Utils::EnumUtils::roleString(person.getRole()));
            }
            return personVector;
        }

        std::vector<BookManager::Entity::Publisher> TableDeserializers::deserializePublisherTable(int limit, int offset)
        {
            std::vector<BookManager::Entity::Publisher> publisherVector;
            SQLite::Statement query(*database, "SELECT * FROM Publishers LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                publisherVector.emplace_back(deserializeOneElementSimpleTableIdAndName<BookManager::Entity::Publisher>(query));
            }

            for(auto publisher : publisherVector)
            {
                LOG_INFO("Publisher : ({}) {}", publisher.getId(), publisher.getName());
            }
            return publisherVector;
        }

        std::vector<BookManager::Category::Category> TableDeserializers::deserializeCategoryTable(int limit, int offset)
        {
            std::vector<BookManager::Category::Category> categoryVector;
            SQLite::Statement query(*database, "SELECT * FROM Category LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                categoryVector.emplace_back(deserializeOneElementSimpleTableIdAndName<BookManager::Category::Category>(query));
            }

            for(auto category : categoryVector)
            {
                LOG_INFO("Category : ({}) {}", category.getId(), category.getName());
            }
            return categoryVector;
        }

        std::vector<BookManager::Entity::BookSerie> TableDeserializers::deserializeBookSerieTable(int limit, int offset)
        {
            std::vector<BookManager::Entity::BookSerie> bookSeriesVector;
            SQLite::Statement query(*database, "SELECT * FROM BookSeries LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                bookSeriesVector.emplace_back(deserializeOneElementSimpleTableIdAndName<BookManager::Entity::BookSerie>(query));
            }

            for(auto bookSerie : bookSeriesVector)
            {
                LOG_INFO("BookSerie : ({}) {}", bookSerie.getId(), bookSerie.getName());
            }
            return bookSeriesVector;
        }

        BookManager::Entity::Person TableDeserializers::deserializeOnePerson(SQLite::Statement& query)
        {
            int id = query.getColumn("id");
            std::string firstName = query.getColumn("firstName");
            std::string lastName = query.getColumn("lastName");
            BookManager::Entity::Role role{query.getColumn("role").getInt()};
            return BookManager::Entity::Person{id, firstName, lastName, role};
        }

    } // namespace Manager
} // namespace BookManager