cmake_minimum_required(VERSION 3.0)


set(LIB_NAME book)

project(${LIB_NAME})

add_subdirectory(Abstract)
add_subdirectory(Factory)
add_subdirectory(Enum)


set(SRCS
    Novel.cpp
    )

set(HEADERS
    ArtBook.hpp
    Comics.hpp
    Manga.hpp
    Novel.hpp
    )

add_library(${LIB_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${LIB_NAME} book_abstract)
# target_include_directories(${LIB_NAME} PUBLIC .)
