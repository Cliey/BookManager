cmake_minimum_required(VERSION 3.0)

set(LIB_NAME entity_enum)
project(${LIB_NAME} CXX)

set(HEADERS
    Role.hpp
    )

add_library(${LIB_NAME} ${HEADERS})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
