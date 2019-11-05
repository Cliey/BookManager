cmake_minimum_required(VERSION 3.0)

set(LIB_NAME Utils)
project(${LIB_NAME}_UT CXX)

set(SRCS
	LoggersUT.cpp
    )

add_executable(${LIB_NAME}_UT ${SRCS})

target_link_libraries(${LIB_NAME}_UT
    PUBLIC
        gtest_main
        utils
)
