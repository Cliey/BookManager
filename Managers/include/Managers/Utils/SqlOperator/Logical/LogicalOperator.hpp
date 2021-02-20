#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <fmt/core.h>
#include <cstdarg>
#include "Managers/Utils/SqlOperator/Comparison/InterfaceComparisonOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/InterfaceLogicalOperator.hpp"

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            class LogicalOperator : public InterfaceLogicalOperator
            {
            public:
                LogicalOperator(std::shared_ptr<InterfaceOperator> op1, std::shared_ptr<InterfaceOperator> op2)
                {
                    operators.push_back(op1);
                    operators.push_back(op2);
                }

                // LogicalOperator(std::shared_ptr<InterfaceComparisonOperator> comparisonOperator, ...)
                // {
                //     va_list args;
                //     va_start(args, comparisonOperator);
                //     const std::size_t sizeArg = sizeof(args);
                //     std::cout << "size= " << sizeArg << std::endl;
                //     ;
                //     for(std::shared_ptr<InterfaceComparisonOperator> currentOperator = va_arg(args, std::shared_ptr<InterfaceComparisonOperator>);
                //         currentOperator != nullptr;
                //         currentOperator = va_arg(args, std::shared_ptr<InterfaceComparisonOperator>))
                //     {
                //         std::cout << " he" << std::endl;
                //         operators.push_back(currentOperator);
                //     }
                //     va_end(args);
                //     // operators.push_back(comparisonOperator);
                // }
                // LogicalOperator(InterfaceComparisonOperator op1, InterfaceComparisonOperator op2...);

                std::string operator()() const override
                {
                    return this->get();
                }

                std::string get() const override
                {
                    std::string strRet;

                    for(int i = 0; i < operators.size() - 1; i++)
                    {
                        strRet += getFormattedString(operators.at(i));
                    }

                    strRet += addLastOperator();

                    return strRet;
                }

                private:
                std::string getFormattedString(std::shared_ptr<InterfaceOperator> currentOperator) const
                {
                    if(std::dynamic_pointer_cast<InterfaceComparisonOperator>(currentOperator))
                        return getStringComparison(currentOperator);
                    else
                        return getStringLogical(currentOperator);
                }

                std::string getStringLogical(std::shared_ptr<InterfaceOperator> logicalOperator) const
                {
                    std::string strOperator = logicalOperator->get();
                    return fmt::format("(({}) {} ", strOperator, getLogicalOperator());

                }

                std::string getStringComparison(std::shared_ptr<InterfaceOperator> comparisonOperator) const
                {
                    std::string strOperator = comparisonOperator->get();
                    return fmt::format("{} {} ", strOperator, getLogicalOperator());
                }

                std::string addLastOperator() const
                {
                    if(auto lastOperator = std::dynamic_pointer_cast<InterfaceComparisonOperator>(operators.back()))
                        return fmt::format("{}", lastOperator->get());
                    else
                        return fmt::format("({}))", operators.back()->get());
                }

                protected:
                std::vector<std::shared_ptr<InterfaceOperator>> operators;
            };
        } // namespace SqlOperator
    } // namespace Manager

} // namespace BookManager