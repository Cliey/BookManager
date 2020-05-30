cmake_minimum_required(VERSION 3.0)

set(LIB_NAME entity_types)

project(${LIB_NAME} CXX)

set(HEADERS
    include/EntityTypes/BookSeries.hpp
    include/EntityTypes/Person.hpp
    include/EntityTypes/Publisher.hpp
    )

add_library(${LIB_NAME} ${HEADERS})
add_library(entity::types ALIAS ${LIB_NAME})
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${LIB_NAME}
    PUBLIC
        utils
    )

target_include_directories(${LIB_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    )