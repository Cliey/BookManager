#pragma once
#include "Managers/Utils/SqlOperator/Logical/LogicalOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/InterfaceComparisonOperator.hpp"
namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            class OrOperator : public LogicalOperator
            {
            public:
                OrOperator(std::shared_ptr<InterfaceComparisonOperator> op1, std::shared_ptr<InterfaceComparisonOperator> op2)
                    : LogicalOperator(op1, op2) {}

                OrOperator(std::shared_ptr<InterfaceLogicalOperator> op1, std::shared_ptr<InterfaceLogicalOperator> op2)
                    : LogicalOperator(op1, op2) {}
            protected:
                std::string getLogicalOperator() const override
                {
                    return "OR";
                }

            };
        } // namespace SqlOperator
    } // namespace Manager
} // namespace BookManager