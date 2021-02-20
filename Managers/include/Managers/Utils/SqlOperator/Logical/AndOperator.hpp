#pragma once
#include "Managers/Utils/SqlOperator/Logical/LogicalOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/InterfaceComparisonOperator.hpp"
namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            class AndOperator : public LogicalOperator
            {
            public:
                AndOperator(std::shared_ptr<InterfaceComparisonOperator> op1, std::shared_ptr<InterfaceComparisonOperator> op2)
                    : LogicalOperator(op1, op2) {}

            protected:
                std::string getLogicalOperator() const override
                {
                    return "AND";
                }

            };
        } // namespace SqlOperator
    } // namespace Manager
} // namespace BookManager