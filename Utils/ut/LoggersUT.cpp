#include "Utils/Log.hpp"
#include <gtest/gtest.h>

class LoggersUT : public ::testing::Test
{
public:
    LoggersUT() = default;
};

TEST_F(LoggersUT, testLogger)
{
    std::string expectedOutput;
    std::string testStr = "testStr";

    /**** LOG_INFO ****/
    LOG_INFO("Test Logger no Args");
    LOG_INFO("Test Logger 1 Args (int) : {}", 23);
    LOG_INFO("Test Logger 1 Args (str) : {}", "myStr");
    LOG_INFO("Test Logger 2 Args (int and str) : {} and {}", 2, "myStr");
    LOG_INFO("Test Logger 2 Args (str and int) : {} and {}", "myStr", 2);
    LOG_INFO("Test Logger 2 Args (str and str) : {} and {}", "myStr", "myStr2");
    LOG_INFO("Test Logger 2 Args (str and str var) : {} and {}", "myStr", testStr);



    /**** LOG_ERROR ****/
    LOG_ERROR("Test Logger no Args");
    LOG_ERROR("Test Logger 1 Args (int) : {}", 23);
    LOG_ERROR("Test Logger 1 Args (str) : {}", "myStr");
    LOG_ERROR("Test Logger 2 Args (int and str) : {} and {}", 2, "myStr");
    LOG_ERROR("Test Logger 2 Args (str and int) : {} and {}", "myStr", 2);
    LOG_ERROR("Test Logger 2 Args (str and str) : {} and {}", "myStr", "myStr2");
    LOG_ERROR("Test Logger 2 Args (str and str var) : {} and {}", "myStr", testStr);

    /**** LOG_WINDOW ****/
    LOG_WINDOW("Test Logger no Args");
    LOG_WINDOW("Test Logger 1 Args (int) : {}", 23);
    LOG_WINDOW("Test Logger 1 Args (str) : {}", "myStr");
    LOG_WINDOW("Test Logger 2 Args (int and str) : {} and {}", 2, "myStr");
    LOG_WINDOW("Test Logger 2 Args (str and int) : {} and {}", "myStr", 2);
    LOG_WINDOW("Test Logger 2 Args (str and str) : {} and {}", "myStr", "myStr2");
    LOG_WINDOW("Test Logger 2 Args (str and str var) : {} and {}", "myStr", testStr);

}
