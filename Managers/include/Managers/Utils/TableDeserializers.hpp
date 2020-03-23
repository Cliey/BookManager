
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <string>
#include <ctime>

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
        enum class BookType;
        enum class BookStatus;
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
                std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> deserializeBookTable(int limit, int offset);

                template<typename T>
                T deserializeOneElementSimpleTableIdAndName(SQLite::Statement&);

                BookManager::Entity::Person deserializeOnePerson(SQLite::Statement&);

            private:
                BookManager::Book::BookType getType(int type);
                BookManager::Book::BookStatus getBookStatus(int status);
                std::time_t convertDate(std::string);
                std::string getElementOfDateAndEraseIt(std::string& date);
                void setOptionalFieldIfExist(std::optional<std::time_t>&, SQLite::Statement&, std::string);
                void setOptionalFieldIfExist(std::optional<double>&, SQLite::Statement&, std::string);
                BookManager::Category::Category getCategoryFromId(int);
                BookManager::Entity::BookSerie getBookSerieFromId(int);
                BookManager::Entity::Publisher getPublisherFromId(int);
                BookManager::Entity::Person getAuthorFromId(int);
                std::vector<std::shared_ptr<Category::Category>> getSubcategory(int);
                std::vector<std::shared_ptr<BookManager::Entity::Person>> getAuthors(int);

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