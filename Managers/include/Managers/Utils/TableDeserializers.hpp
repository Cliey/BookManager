
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
                TableDeserializers(SQLite::Database& database) : database(std::move(database)) {}
                std::vector<BookManager::Entity::Person> deserializePersonTable(int limit, int offset);
                std::vector<BookManager::Entity::Publisher> deserializePublisherTable(int limit, int offset);
                std::vector<BookManager::Category::Category> deserializeCategoryTable(int limit, int offset);

            private:
                SQLite::Database database;
        };
    } // namespace Manager
} // namespace BookManager