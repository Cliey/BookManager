cmake_minimum_required(VERSION 3.0)

set(LIB_NAME graphical_interface_models)
project(${LIB_NAME}_UT CXX)

set(SRCS
	CategoryModelUT.cpp
	PersonModelUT.cpp
    )

add_executable(${LIB_NAME}_UT ${SRCS})

target_link_libraries(${LIB_NAME}_UT
    PUBLIC
        gtest_main
    PRIVATE
        graphical_interface_models
)
