cmake_minimum_required(VERSION 3.0)

set(LIB_NAME managers)
project(${LIB_NAME}_UT CXX)

set(SRCS
	DatabaseManagerUT.cpp
	DatabaseManagerBookUT.cpp
	SettingsManagerUT.cpp
    )

add_executable(${LIB_NAME}_UT ${SRCS})

target_link_libraries(${LIB_NAME}_UT
    PUBLIC
        gtest_main
        maillon_creation
        managers
        utils
    PRIVATE
        SQLiteCpp
        sqlite3
)
