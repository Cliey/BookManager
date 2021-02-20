#include "Utils/TestUtils.hpp"

template <>
void CheckOptionalField::check<double>(std::optional<double> optionalToCheck, std::optional<double> optionalExpected)
{
    EXPECT_EQ(optionalToCheck.has_value(), optionalExpected.has_value());
    if(optionalToCheck.has_value())
    {
        EXPECT_DOUBLE_EQ(optionalToCheck.value(), optionalExpected.value());
    }
}

