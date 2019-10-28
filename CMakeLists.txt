cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER /cygdrive/c/cygwin64/bin/g++.exe --std=gnu++1z)



# Project Name
project(BookManager CXX)

add_subdirectory(Book)
add_subdirectory(Entity)
add_subdirectory(MaillonCreation)
add_subdirectory(Managers)
add_subdirectory(Utils)
add_subdirectory(Lib)

# Google Test
add_subdirectory(3rd_party/google-test)
enable_testing()

# SQLiteCpp
# add SQLite3 C++ wrapper arround sqlite3 library (and sqlite3 itself provided for ease of use)
# NOTE: here you can set CMake variables to avoid building Example, as well as cpplint, cppcheck...
# NOTE: or set them in the cmake commande line (see for instance provided build.bat/build.sh scripts)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/3rd_party/SQLiteCpp)

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
