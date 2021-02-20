#pragma once
#include <string>

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            class InterfaceOperator
            {
            public:
                virtual std::string operator()() const = 0;
                virtual std::string get() const = 0;
            };
        } // namespace SqlOperator
    } // namespace Manager

} // namespace BookManager