cmake_minimum_required(VERSION 3.0)

set(LIB_NAME book)

project(${LIB_NAME})

add_subdirectory(BookAbstract)
add_subdirectory(BookEnum)
add_subdirectory(BookFactory)
add_subdirectory(BookTypes)
