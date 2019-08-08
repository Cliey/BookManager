cmake_minimum_required(VERSION 3.0)

project(book CXX)
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

add_library(book ${SRCS} ${HEADERS})
target_link_libraries(book book_abstract)
# target_include_directories(book PUBLIC .)
