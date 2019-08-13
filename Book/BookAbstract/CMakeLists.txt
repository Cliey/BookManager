cmake_minimum_required(VERSION 3.0)

set(LIB_NAME book_abstract)

project(${LIB_NAME})

set(SRCS
    src/Book.cpp
    src/DrawBook.cpp
    )

set(HEADERS
    include/BookAbstract/Book.hpp
    include/BookAbstract/DrawBook.hpp
    )

add_library(${LIB_NAME} ${SRCS})
add_library(book::abstract ALIAS ${LIB_NAME})

target_link_libraries(${LIB_NAME}
    PUBLIC
        book::enum
    )

target_include_directories(book_abstract
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    )
