cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER /cygdrive/c/cygwin64/bin/g++.exe --std=c++1z)
#set(CMAKE_C_COMPILER_WORKS 1)
#set(CMAKE_CXX_COMPILER_WORKS 1)

# Project Name
project(BookManager CXX)

add_subdirectory(Book)
add_subdirectory(MaillonCreation)
add_subdirectory(Managers)
add_subdirectory(Utils)

set(SRCS
	main.cpp
    )

set(HEADERS
	Category.hpp
	Person.hpp
	Publisher.hpp
	Role.hpp
    )

# Exectuable name is BookManager, compiled from files stored in SRCS and HEADERS
add_executable(BookManager ${SRCS} ${HEADERS})
target_link_libraries(BookManager book book_factory maillon_creation managers utils)
