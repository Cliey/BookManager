#pragma once
#include "Managers/Utils/SqlOperator/Logical/InterfaceLogicalOperator.hpp"

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            template<class T>
            class InOperator : public InterfaceLogicalOperator
            {
            public:
                InOperator(std::string field, std::vector<T> vector)
                    : field(field), vector(vector) {}

                std::string operator()() const override
                {
                    return this->get();
                }

                std::string get() const override
                {
                    std::string strRet =  fmt::format("{} IN (", field);

                    for(int i = 0; i < vector.size() - 1; i++)
                    {
                        strRet += fmt::format("{}, ", vector.at(i));
                    }
                    strRet += fmt::format("{})", vector.back());

                    return strRet;
                }

            protected:
                std::string getLogicalOperator() const override
                {
                    return "IN";
                }
            private:
                std::string field;
                std::vector<T> vector;

            };
        } // namespace SqlOperator
    } // namespace Manager
} // namespace BookManager