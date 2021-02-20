#include <string>
#include <memory>
#include <fmt/core.h>
#include "Managers/Utils/SqlOperator/WhereOperator.hpp"

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            WhereOperator::WhereOperator(std::shared_ptr<InterfaceOperator> sqlOperator)
                : sqlOperator(sqlOperator)
            {
            }

            std::string WhereOperator::get()
            {
                if(sqlOperator)
                {
                    return fmt::format("WHERE {}", sqlOperator->get());
                }
                return "no";
            }

        } // namespace SqlOperator
    } // namespace Manager

} // namespace BookManager