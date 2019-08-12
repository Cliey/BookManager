cmake_minimum_required(VERSION 3.0)

set(LIB_NAME book_abstract)

project(${LIB_NAME})

set(SRCS
    Book.cpp
    DrawBook.cpp
    )

set(HEADERS
    Book.hpp
    DrawBook.hpp
    )

add_library(${LIB_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${LIB_NAME} book_enum)
# target_include_directories(book_abstract PUBLIC .)
