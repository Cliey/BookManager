cmake_minimum_required(VERSION 3.0)

set(LIB_NAME managers)
project(${LIB_NAME} CXX)


set(SRCS
	Manager.cpp
    )

set(HEADERS
	Manager.hpp
    )

add_library(${LIB_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${LIB_NAME} PUBLIC book_factory maillon_creation lib)
# target_include_directories(maillon_creation PUBLIC .)
