cmake_minimum_required(VERSION 3.0)

project(utils CXX)

set(SRCS
    Utils.cpp
    )

set(HEADERS
    Utils.hpp
    )

add_library(utils ${SRCS} ${HEADERS})
target_link_libraries(utils book_enum)
