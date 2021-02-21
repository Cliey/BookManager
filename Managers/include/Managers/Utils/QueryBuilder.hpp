#pragma once
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h>

namespace BookManager
{
    namespace Entity
    {
        class BookSeries;
        class Person;
        class Publisher;
        enum class Role;
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
        namespace SqlOperator
        {
            class InterfaceOperator;
        }
        class QueryBuilder // QueryBuilder()
        {
            public:

                enum class Order {
                    ASCENDANT = 0,
                    DESCENDANT = 1,
                };

                QueryBuilder() = default;
                QueryBuilder selectFrom(std::string tableName);
                QueryBuilder where(const std::shared_ptr<SqlOperator::InterfaceOperator>& op);
                /*
                    QueryBuilder where(std::string field, IComparable comparable);
                    where(AND("field", value, "field", value), OR(AND("field", value, "field", value)))
                */
                QueryBuilder limit(int limit);
                QueryBuilder offset(int offset);
                QueryBuilder orderBy(std::string field, Order order); // (, ...) variadic

                std::string getQuery();

                void reset()
                {
                    selectStatementSet = false;
                    whereStatementSet = false;
                    limitStatementSet = false;
                    offsetStatementSet = false;
                    orderByStatementSet = false;
                    queryStr.clear();
                }

            private:
                std::string queryStr;

                bool selectStatementSet = false;
                bool whereStatementSet = false;
                bool limitStatementSet = false;
                bool offsetStatementSet = false;
                bool orderByStatementSet = false;

                std::string getOrder(Order order);
        };
    } // namespace Manager
} // namespace BookManager