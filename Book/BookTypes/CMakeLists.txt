cmake_minimum_required(VERSION 3.0)

set(LIB_NAME book_types)

project(${LIB_NAME})

set(SRCS
    src/Novel.cpp
    )

set(HEADERS
    include/BookTypes/ArtBook.hpp
    include/BookTypes/Comics.hpp
    include/BookTypes/Manga.hpp
    include/BookTypes/Novel.hpp
    )

add_library(${LIB_NAME} ${SRCS})
add_library(book::types ALIAS ${LIB_NAME})

target_link_libraries(${LIB_NAME}
    PUBLIC
        book::abstract)

target_include_directories(${LIB_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        src)
