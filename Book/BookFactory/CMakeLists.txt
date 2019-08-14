cmake_minimum_required(VERSION 3.0)

set(LIB_NAME book_factory)

project(${LIB_NAME})

set(SRCS
    src/BookFactory.cpp
    )

set(HEADERS
    include/BookFactory/BookFactory.hpp
    )

add_library(${LIB_NAME} ${SRCS})
add_library(book::factory ALIAS ${LIB_NAME})

target_link_libraries(${LIB_NAME}
    PUBLIC
        book::abstract
        maillon_creation
    )

target_include_directories(${LIB_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        src
    )
