cmake_minimum_required(VERSION 3.0)

project(entity)
add_subdirectory(Enum)

set(HEADERS
    Person.hpp
    Publisher.hpp
    )

add_library(entity ${HEADERS})
set_target_properties(entity PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(entity utils)
