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
            SQLite::Statement query(*database, "SELECT * FROM Categories LIMIT :limit OFFSET :offset");
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
            std::string firstName = query.getColumn("first_name");
            std::string lastName = query.getColumn("last_name");
            BookManager::Entity::Role role{query.getColumn("role").getInt()};
            return BookManager::Entity::Person{id, firstName, lastName, role};
        }

        BookManager::Book::BookType TableDeserializers::getType(int type)
        {
            switch(type)
            {
                case 0:
                    return BookManager::Book::BookType::ArtBook;
                case 1:
                    return BookManager::Book::BookType::Comics;
                case 2:
                    return BookManager::Book::BookType::Manga;
                case 3:
                    return BookManager::Book::BookType::Novel;
            }
        }

        BookManager::Book::BookStatus TableDeserializers::getBookStatus(int status)
        {
            switch(status)
            {
                case 0:
                    return BookManager::Book::BookStatus::Listed;
                case 1:
                    return BookManager::Book::BookStatus::HaveIt;
                case 2:
                    return BookManager::Book::BookStatus::WantIt;
            }
        }

        std::string TableDeserializers::getElementOfDateAndEraseIt(std::string& date)
        {
            std::size_t posDash =  date.find("-");
            std::string element = date.substr(0, posDash);
            date.erase(0, posDash + 1);
            return element;
        }

        std::time_t TableDeserializers::convertDate(std::string date)
        {
            std::string year = getElementOfDateAndEraseIt(date);
            std::string month = getElementOfDateAndEraseIt(date);
            std::string day = date;
            std::tm returnDate{};
            returnDate.tm_year = std::stoi(year) - 1900; // Year since 1900
            returnDate.tm_mon = std::stoi(month) - 1; // 0 to 11
            returnDate.tm_mday = std::stoi(day);
            return std::mktime(&returnDate);
        }

        void TableDeserializers::setOptionalFieldIfExist(std::optional<std::time_t>& fieldToInit, SQLite::Statement& query, std::string column)
        {
            if(query.isColumnNull(column.c_str()))
                return;

            auto field = query.getColumn(column.c_str());
            fieldToInit = std::make_optional<std::time_t>(convertDate(field));
        }

        void TableDeserializers::setOptionalFieldIfExist(std::optional<double>& fieldToInit, SQLite::Statement& query, std::string column)
        {
            if(query.isColumnNull(column.c_str()))
                return;

            auto field = query.getColumn(column.c_str());
            fieldToInit = std::make_optional<double>(field);
        }

        BookManager::Category::Category TableDeserializers::getCategoryFromId(int id)
        {
            SQLite::Statement query(*database, "SELECT * FROM Categories WHERE id=:id");
            query.bind(":id", id);
            query.executeStep();
            return deserializeOneElementSimpleTableIdAndName<BookManager::Category::Category>(query);
        }

        BookManager::Entity::BookSerie TableDeserializers::getBookSerieFromId(int id)
        {
            SQLite::Statement query(*database, "SELECT * FROM BookSeries WHERE id=:id");
            query.bind(":id", id);
            query.executeStep();
            return deserializeOneElementSimpleTableIdAndName<BookManager::Entity::BookSerie>(query);
        }

        BookManager::Entity::Publisher TableDeserializers::getPublisherFromId(int id)
        {
            SQLite::Statement query(*database, "SELECT * FROM Publishers WHERE id=:id");
            query.bind(":id", id);
            query.executeStep();
            return deserializeOneElementSimpleTableIdAndName<BookManager::Entity::Publisher>(query);
        }

        std::vector<std::shared_ptr<BookManager::Category::Category>> TableDeserializers::getSubcategory(int bookId)
        {
            SQLite::Statement query(*database, "SELECT * FROM Books_SubCategories WHERE bookId=:bookId");
            query.bind(":bookId", bookId);
            std::vector<std::shared_ptr<BookManager::Category::Category>> subCategory;
            while(query.executeStep())
            {
                int categoryId = query.getColumn("subCategoryId");
                subCategory.push_back(
                    std::make_shared<BookManager::Category::Category>(getCategoryFromId(categoryId)));
            }
            return subCategory;
        }

        BookManager::Entity::Person TableDeserializers::getAuthorFromId(int id)
        {
            SQLite::Statement query(*database, "SELECT * FROM Persons WHERE id=:id");
            query.bind(":id", id);
            query.executeStep();
            return deserializeOnePerson(query);
        }

        std::vector<std::shared_ptr<BookManager::Entity::Person>> TableDeserializers::getAuthors(int bookId)
        {
            SQLite::Statement query(*database, "SELECT * FROM Books_Persons WHERE bookId=:bookId");
            query.bind(":bookId", bookId);
            std::vector<std::shared_ptr<BookManager::Entity::Person>> authors;
            while(query.executeStep())
            {
                int authorId = query.getColumn("personId");
                authors.push_back(
                    std::make_shared<BookManager::Entity::Person>(getAuthorFromId(authorId)));
            }
            return authors;
        }

        std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> TableDeserializers::deserializeBookTable(int limit, int offset)
        {
            std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> bookVector;
            SQLite::Statement query(*database, "SELECT * FROM Books LIMIT :limit OFFSET :offset");
            query.bind(":limit", limit);
            query.bind(":offset", offset);

            while(query.executeStep())
            {
                BookManager::Book::BookType type = getType(query.getColumn("type"));
                std::shared_ptr<BookManager::Book::Abstraction::Book> newBook = BookManager::Book::BookFactory::create(type);
                int bookId = query.getColumn("id");
                newBook->id = bookId;

                std::string title = query.getColumn("title");
                newBook->generalInfo.title = title;
                newBook->generalInfo.author = getAuthors(bookId);

                int mainCategory = query.getColumn("main_category");
                newBook->categoryInfo.mainCategory = std::make_shared<BookManager::Category::Category>(getCategoryFromId(mainCategory));
                newBook->categoryInfo.subCategory = getSubcategory(bookId);

                int publisher = query.getColumn("publisher");
                newBook->generalInfo.publisher = std::make_shared<BookManager::Entity::Publisher>(getPublisherFromId(publisher));

                setOptionalFieldIfExist(newBook->generalInfo.published, query, "published_date");

                if(!query.isColumnNull("book_serie"))
                {
                    int bookSerie = query.getColumn("book_serie");
                    newBook->generalInfo.bookSerie = std::make_shared<BookManager::Entity::BookSerie>(getBookSerieFromId(bookSerie));
                }

                setOptionalFieldIfExist(newBook->statInfo.purchasedDate, query, "purchased_date");
                setOptionalFieldIfExist(newBook->statInfo.price, query, "price");
                newBook->additionalInfo.status = getBookStatus(query.getColumn("status"));
                int isRead = query.getColumn("is_read");
                newBook->additionalInfo.isRead = static_cast<bool>(isRead);
                setOptionalFieldIfExist(newBook->statInfo.startReadingDate, query, "start_reading_date");
                setOptionalFieldIfExist(newBook->statInfo.endReadingDate, query, "end_reading_date");

                if(!query.isColumnNull("rate"))
                {
                    newBook->additionalInfo.rate = query.getColumn("rate");
                }

                bookVector.push_back(newBook);
            }

            for(auto& book : bookVector)
            {
                LOG_INFO("Book : ({}) {}", book->id, book->generalInfo.title);
            }
            return bookVector;
        }
    } // namespace Manager
} // namespace BookManager