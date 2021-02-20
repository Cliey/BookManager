#pragma once
#include "Managers/Utils/SqlOperator/Logical/LogicalOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/InterfaceComparisonOperator.hpp"

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            class NotOperator : public InterfaceLogicalOperator
            {
            public:
                NotOperator(std::shared_ptr<InterfaceComparisonOperator> comparaisonOperator)
                    : comparaisonOperator(comparaisonOperator) {}

                std::string operator()() const override
                {
                    return this->get();
                }

                std::string get() const override
                {
                    std::string strRet = fmt::format("NOT ({})", comparaisonOperator->get() );
                    return strRet;
                }

            protected:
                std::string getLogicalOperator() const override
                {
                    return "NOT";
                }

            private:
                std::shared_ptr<InterfaceComparisonOperator> comparaisonOperator;

            };
        } // namespace SqlOperator
    } // namespace Manager
} // namespace BookManager