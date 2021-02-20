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
                // LogicalOperator(LogicalOperator logicalOperator);
                LogicalOperator(std::shared_ptr<InterfaceOperator> op1, std::shared_ptr<InterfaceOperator> op2)
                {
                    operators.push_back(op1);
                    operators.push_back(op2);
                }

                // LogicalOperator(std::shared_ptr<InterfaceLogicalOperator> op1, std::shared_ptr<InterfaceLogicalOperator> op2)
                // {
                //     logicOperators.push_back(op1);
                //     logicOperators.push_back(op2);
                // }

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
                    return this->getForComparisionOperator();
                }

                private:
                std::string getForComparisionOperator() const
                {
                    std::string strRet;

                    for(int i = 0; i < operators.size() - 1; i++)
                    {
                        std::string strOperator = operators.at(i)->get();
                        strRet += fmt::format("(({}) {} ", strOperator, getLogicalOperator());
                    }
                    strRet += fmt::format("({}))", operators.back()->get());

                    return strRet;
                }

                std::string getForLogicalOperator() const
                {
                    std::string strRet;

                    for(int i = 0; i < logicOperators.size() - 1; i++)
                    {
                        std::string strOperator = logicOperators.at(i)->get();
                        strRet += fmt::format("(({}) {} ", strOperator, getLogicalOperator());
                    }
                    strRet += fmt::format("({}))", logicOperators.back()->get());

                    return strRet;
                }


                protected:
                // std::vector<std::shared_ptr<InterfaceComparisonOperator>> operators;
                std::vector<std::shared_ptr<InterfaceLogicalOperator>> logicOperators;
                std::vector<std::shared_ptr<InterfaceOperator>> operators;
            };
        } // namespace SqlOperator
    } // namespace Manager

} // namespace BookManager