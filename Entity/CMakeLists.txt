cmake_minimum_required(VERSION 3.0)

set(LIB_NAME entity)

project(${LIB_NAME})

add_subdirectory(Enum)

set(HEADERS
    Person.hpp
    Publisher.hpp
    )

add_library(${LIB_NAME} ${HEADERS})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${LIB_NAME} utils)
