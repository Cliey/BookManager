cmake_minimum_required(VERSION 3.0)

set(LIB_NAME book_enum)

project(${LIB_NAME})

set(HEADERS
    include/BookEnum/BookStatus.hpp
    include/BookEnum/BookType.hpp
    )

add_library(${LIB_NAME} ${HEADERS})
add_library(book::enum ALIAS ${LIB_NAME})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${LIB_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    )
