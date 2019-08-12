cmake_minimum_required(VERSION 3.0)

set(LIB_NAME book_factory)

project(${LIB_NAME})

set(SRCS
    BookFactory.cpp
    )

set(HEADERS
    BookFactory.hpp
    )

add_library(${LIB_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${LIB_NAME} book_abstract)
# target_include_directories(${LIB_NAME} PUBLIC .)
