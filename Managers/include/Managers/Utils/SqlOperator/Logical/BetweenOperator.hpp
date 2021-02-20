#pragma once
#include "Managers/Utils/SqlOperator/Logical/InterfaceLogicalOperator.hpp"

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            template<class T>
            class BetweenOperator : public InterfaceLogicalOperator
            {
            public:
                BetweenOperator(std::string field, T value1, T value2)
                    : field(field), value1(value1), value2(value2) {}

                std::string operator()() const override
                {
                    return this->get();
                }

                 std::string get() const override
                {
                    std::string strRet = fmt::format("{} BETWEEN {} AND {}", field, value1, value2);
                    return strRet;
                }

            protected:
                std::string getLogicalOperator() const override
                {
                    return "BETWEEN";
                }
            private:
                std::string field;
                T value1;
                T value2;

            };
        } // namespace SqlOperator
    } // namespace Manager
} // namespace BookManager