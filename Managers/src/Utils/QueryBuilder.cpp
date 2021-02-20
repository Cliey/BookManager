#include "Managers/Utils/QueryBuilder.hpp"
#include "Managers/Utils/SqlOperator/InterfaceOperator.hpp"
#include <fmt/core.h>

namespace BookManager
{
    namespace Manager
    {
        QueryBuilder QueryBuilder::selectFrom(std::string tableName)
        {
            if(selectStatementSet)
                return *this;

            queryStr += fmt::format("SELECT * FROM {}", tableName);
            selectStatementSet = true;
            return *this;
        }

        QueryBuilder QueryBuilder::where(std::shared_ptr<SqlOperator::InterfaceOperator> op)
        {
            if(whereStatementSet)
                return *this;

            queryStr += fmt::format(" WHERE {}", op->get());
            whereStatementSet = true;
            return *this;
        }

        QueryBuilder QueryBuilder::limit(int limit)
        {
            if(limitStatementSet)
                return *this;

            queryStr += fmt::format(" LIMIT {}", limit);
            limitStatementSet = true;
            return *this;
        }

        QueryBuilder QueryBuilder::offset(int offset)
        {
            if(offsetStatementSet)
                return *this;

            queryStr += fmt::format(" OFFSET {}", offset);
            offsetStatementSet = true;
            return *this;
        }

        QueryBuilder QueryBuilder::orderBy(std::string field, Order order)
        {
            if(orderByStatementSet)
                return *this;

            queryStr += fmt::format(" ORDER BY {} {}", field, getOrder(order));
            orderByStatementSet = true;
            return *this;
        }

        std::string QueryBuilder::getOrder(Order order)
        {
            switch(order)
            {
                case Order::ASCENDANT:
                    return "ASC";
                case Order::DESCENDANT:
                    return "DESC";
                default:
                    return "ASC";
            }
        }

        std::string QueryBuilder::getQuery()
        {
            return queryStr;
        }
    } // namespace Manager
} // namespace BookManager