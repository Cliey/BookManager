cmake_minimum_required(VERSION 3.0)

project(book_enum CXX)

set(HEADERS
    BookStatus.hpp
    BookType.hpp)

add_library(book_enum ${HEADERS})
set_target_properties(book_enum PROPERTIES LINKER_LANGUAGE CXX)
