cmake_minimum_required(VERSION 3.0)

set(LIB_NAME book_enum)

project(${LIB_NAME})

set(HEADERS
    BookStatus.hpp
    BookType.hpp)

add_library(${LIB_NAME} ${HEADERS})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
