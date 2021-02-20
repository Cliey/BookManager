cmake_minimum_required(VERSION 3.0)

set(LIB_NAME managers)
project(${LIB_NAME}_UT CXX)

set(SRCS
	DatabaseManagerUT.cpp
	SettingsManagerUT.cpp
	TableDeserializersUT.cpp
	TableDeserializersBookUT.cpp
	TableDeleteUT.cpp
	TableInsertUT.cpp
	QueryBuilderUT.cpp
	TableUpdaterUT.cpp
	SqlOperatorUT.cpp
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
