
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

namespace BookManager
{
    namespace Entity
    {
        class Person;
        class Publisher;
    }
    namespace Category
    {
        class Category;
    }
    namespace Manager
    {
        class TableDeserializers
        {
            public:
                static std::vector<BookManager::Entity::Person> deserializePersonTable(SQLite::Database& database, int limit, int offset);
                static std::vector<BookManager::Entity::Publisher> deserializePublisherTable(SQLite::Database& database, int limit, int offset);
                static std::vector<BookManager::Category::Category> deserializeCategoryTable(SQLite::Database& database, int limit, int offset);
        };
    } // namespace Manager
} // namespace BookManager