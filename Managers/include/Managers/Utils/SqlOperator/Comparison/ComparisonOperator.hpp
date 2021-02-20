#pragma once
#include <string>
#include "Managers/Utils/SqlOperator/Comparison/InterfaceComparisonOperator.hpp"
namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            template<class T>
            class ComparisonOperator : public InterfaceComparisonOperator
            {
            public:
                ComparisonOperator(std::string field, T value) : field(field), value(value) {}

                protected:
                std::string field;
                T value;
            };
        } // namespace SqlOperator
    } // namespace Manager
} // namespace BookManager