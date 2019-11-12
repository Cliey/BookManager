cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER /cygdrive/c/cygwin64/bin/g++.exe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Activate Coverage when buidling
option(BM_COVERAGE "Activate Coverage compilation" OFF)
if (BM_COVERAGE)
    message ("Compile with Coverage option")
    find_program( GCOV_PATH gcov )
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
endif ()


# Project Name
project(BookManager CXX)

add_subdirectory(Book)
add_subdirectory(Entity)
add_subdirectory(MaillonCreation)
add_subdirectory(Managers)
add_subdirectory(Utils)

# Google Test
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd_party/google-test)
enable_testing()

# SQLiteCpp
# Deactivate cppcheck and cpplint for SQLite
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd_party/SQLiteCpp)

# Fmtlib
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd_party/fmtlib)

# Nlohmann Json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd_party/nlohmann_json)

set(SRCS
	main.cpp
    )

set(HEADERS
	Category.hpp
    )

# Exectuable name is BookManager, compiled from files stored in SRCS and HEADERS
add_executable(BookManager ${SRCS} ${HEADERS})
target_link_libraries(BookManager
    PRIVATE
        book::types
        book::factory
        entity::types
        maillon_creation
        managers
        utils
    )

# UTs
add_test(NAME managers_UT COMMAND managers_UT)
add_test(NAME loggers_UT COMMAND loggers_UT)

unset(BM_COVERAGE)