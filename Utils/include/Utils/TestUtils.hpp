#pragma once
#include <optional>
#include <gtest/gtest.h>

class CheckOptionalField
{
public:
    template <typename T>
    static void check(std::optional<T> optionalToCheck, std::optional<T> optionalExpected);
};

template <typename T>
void CheckOptionalField::check(std::optional<T> optionalToCheck, std::optional<T> optionalExpected)
{
    EXPECT_EQ(optionalToCheck.has_value(), optionalExpected.has_value());
    if(optionalToCheck.has_value())
    {
        EXPECT_EQ(optionalToCheck.value(), optionalExpected.value());
    }
}