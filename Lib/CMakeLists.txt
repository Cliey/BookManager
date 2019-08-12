cmake_minimum_required(VERSION 3.0)

set(LIB_NAME lib)
project(${LIB_NAME} CXX)

# add_subdirectory(json)

set(SRCS
	dummy.cpp
    )

set(HEADERS
    json.hpp
    )

add_library(${LIB_NAME} ${SRCS} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC .)


