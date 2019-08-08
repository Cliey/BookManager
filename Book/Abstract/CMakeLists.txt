cmake_minimum_required(VERSION 3.0)

project(book_abstract CXX)

set(SRCS
    Book.cpp
    DrawBook.cpp
    )

set(HEADERS
    Book.hpp
    DrawBook.hpp
    )

add_library(book_abstract ${SRCS} ${HEADERS})
target_link_libraries(book_abstract book_enum)
# target_include_directories(book_abstract PUBLIC .)
