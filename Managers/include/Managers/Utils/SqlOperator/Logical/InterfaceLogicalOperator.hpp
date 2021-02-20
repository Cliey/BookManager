#pragma once
#include <string>
#include "Managers/Utils/SqlOperator/InterfaceOperator.hpp"

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            class InterfaceLogicalOperator : public InterfaceOperator
            {
            protected:
                virtual std::string getLogicalOperator() const = 0;
            };
        } // namespace SqlOperator
    } // namespace Manager

} // namespace BookManager