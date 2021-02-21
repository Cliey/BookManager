#pragma once
#include "Managers/Utils/SqlOperator/Comparison/ComparisonOperator.hpp"
#include <string>
#include <fmt/core.h>

namespace BookManager
{
    namespace Manager
    {
        namespace SqlOperator
        {
            template<class T>
            class LikeOperator : public ComparisonOperator<T>
            {
            public:
                LikeOperator(std::string field, T value)
                    : ComparisonOperator<T>(field, value) {}

                std::string operator()() const override
                {
                   return this->get();
                }

                std::string get() const override
                {
                    std::string str = fmt::format("{} LIKE '{}'", this->field, this->value);
                    return str;
                }
            };
        } // namespace SqlOperator
    } // namespace Manager
} // namespace BookManager