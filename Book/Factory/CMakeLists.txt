cmake_minimum_required(VERSION 3.0)

project(book_factory CXX)

set(SRCS
    BookFactory.cpp
    )

set(HEADERS
    BookFactory.hpp
    )

add_library(book_factory ${SRCS} ${HEADERS})
target_link_libraries(book_factory book_abstract)
# target_include_directories(book_factory PUBLIC .)
