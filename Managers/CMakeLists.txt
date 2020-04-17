cmake_minimum_required(VERSION 3.0)

set(LIB_NAME managers)
project(${LIB_NAME} CXX)

add_subdirectory(ut)


set(SRCS
	src/GeneralManager.cpp
	src/DatabaseManager.cpp
	src/SettingsManager.cpp
	src/Utils/SettingsTypes.cpp
	src/Utils/TableDeserializers.cpp
	src/Utils/TableDelete.cpp
	src/Utils/TableInsert.cpp
	src/Utils/TableModifier.cpp
	src/Utils/TableUpdater.cpp
    )

set(HEADERS
	include/Manager/GeneralManager.hpp
	include/Manager/DatabaseManager.hpp
	include/Manager/SettingsManager.hpp
	include/Manager/Utils/SortingEnum.hpp
	include/Manager/Utils/SettingsTypes.hpp
	include/Manager/Utils/TableDeserializers.hpp
	include/Manager/Utils/TableDelete.hpp
	include/Manager/Utils/TableInsert.hpp
	include/Manager/Utils/TableModifier.hpp
	include/Manager/Utils/TableUpdater.hpp
    )

add_library(${LIB_NAME} ${SRCS})
target_link_libraries(${LIB_NAME}
    PUBLIC
        book::factory
        maillon_creation
        utils
        nlohmann_json::nlohmann_json
        entity::types
    PRIVATE
        SQLiteCpp
        sqlite3
    )

target_include_directories(managers
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        src
    )
