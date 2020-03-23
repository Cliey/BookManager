
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>

namespace BookManager
{
    namespace Entity
    {
        class BookSerie;
        class Person;
        class Publisher;
    }
    namespace Category
    {
        class Category;
    }
    namespace Book
	{
        namespace Abstraction
        {
            class Book;
        }
    }

    namespace Manager
    {
        class TableDeserializers
        {
            public:
                TableDeserializers(std::shared_ptr<SQLite::Database> database) : database(database) {}
                std::vector<BookManager::Entity::Person> deserializePersonTable(int limit, int offset);
                std::vector<BookManager::Entity::Publisher> deserializePublisherTable(int limit, int offset);
                std::vector<BookManager::Category::Category> deserializeCategoryTable(int limit, int offset);
                std::vector<BookManager::Entity::BookSerie> deserializeBookSerieTable(int limit, int offset);

                template<typename T>
                T deserializeOneElementSimpleTableIdAndName(SQLite::Statement&);

                BookManager::Entity::Person deserializeOnePerson(SQLite::Statement&);

            private:
                std::shared_ptr<SQLite::Database> database;
        };

        template<typename T>
        T TableDeserializers::deserializeOneElementSimpleTableIdAndName(SQLite::Statement& query)
        {
            int id = query.getColumn("id");
            std::string name = query.getColumn("name");
            return T{id, name};
        }
    } // namespace Manager
} // namespace BookManager