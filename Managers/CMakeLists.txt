cmake_minimum_required(VERSION 3.0)

project(managers CXX)

set(SRCS
	Manager.cpp
    )

set(HEADERS
	Manager.hpp
    )

add_library(managers ${SRCS} ${HEADERS})
target_link_libraries(managers book_factory maillon_creation)
# target_include_directories(maillon_creation PUBLIC .)
