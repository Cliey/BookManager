cmake_minimum_required(VERSION 3.0)

set(LIB_NAME managers)
project(${LIB_NAME}_UT CXX)

set(SRCS
	SettingsManagerUT.cpp
    )

add_executable(${LIB_NAME}_UT SettingsManagerUT.cpp)

target_link_libraries(${LIB_NAME}_UT
    gtest_main
    managers
)

add_test(${LIB_NAME}_UT ${LIB_NAME}_UT)