#pragma once
#include <string>
#include <memory>
#include "Managers/Utils/SqlOperator/InterfaceOperator.hpp"

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            class WhereOperator
            {
            public:
                WhereOperator(std::shared_ptr<InterfaceOperator> sqlOperator);

                std::string get();

            private:
                std::shared_ptr<InterfaceOperator> sqlOperator;
            };
        } // namespace SqlOperator
    } // namespace Manager

} // namespace BookManager