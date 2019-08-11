cmake_minimum_required(VERSION 3.0)

project(entity_enum CXX)

set(HEADERS
    Role.hpp
    )

add_library(entity_enum ${HEADERS})
set_target_properties(entity_enum PROPERTIES LINKER_LANGUAGE CXX)
