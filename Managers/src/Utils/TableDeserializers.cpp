#include "Managers/Utils/TableDeserializers.hpp"
#include "Utils/Log.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "Utils/EnumUtils.hpp"
#include "../../../Category.hpp"

namespace BookManager
{
    namespace Manager
    {
        std::vector<BookManager::Entity::Person> TableDeserializers::deserializePersonTable(SQLite::Database& database, int limit, int offset)
        {
            std::vector<BookManager::Entity::Person> personVector;
            SQLite::Statement query(database, "SELECT * FROM Persons LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                int id = query.getColumn("id");
                std::string firstName = query.getColumn("firstName");
                std::string lastName = query.getColumn("lastName");
                BookManager::Entity::Role role{query.getColumn("role").getInt()};
                personVector.emplace_back(BookManager::Entity::Person{id, firstName, lastName, role});
            }

            for(auto person : personVector)
            {
                LOG_INFO("Person : ({}) {} {} is a(n) {}",
                    person.getId(), person.getFirstName(), person.getLastName(), Utils::EnumUtils::roleString(person.getRole()));
            }
            return personVector;
        }

        std::vector<BookManager::Entity::Publisher> TableDeserializers::deserializePublisherTable(SQLite::Database& database, int limit, int offset)
        {
            std::vector<BookManager::Entity::Publisher> publisherVector;
            SQLite::Statement query(database, "SELECT * FROM Publishers LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                int id = query.getColumn("id");
                std::string name = query.getColumn("name");
                publisherVector.emplace_back(BookManager::Entity::Publisher{id, name});
            }

            for(auto publisher : publisherVector)
            {
                LOG_INFO("Publisher : ({}) {}", publisher.getId(), publisher.getName());
            }
            return publisherVector;
        }

        std::vector<BookManager::Category::Category> TableDeserializers::deserializeCategoryTable(SQLite::Database& database, int limit, int offset)
        {
            std::vector<BookManager::Category::Category> categoryVector;
            SQLite::Statement query(database, "SELECT * FROM Publishers LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                int id = query.getColumn("id");
                std::string name = query.getColumn("name");
                categoryVector.emplace_back(BookManager::Category::Category{id, name});
            }

            for(auto category : categoryVector)
            {
                LOG_INFO("Category : ({}) {}", category.getId(), category.getName());
            }
            return categoryVector;
        }
    } // namespace Manager
} // namespace BookManager