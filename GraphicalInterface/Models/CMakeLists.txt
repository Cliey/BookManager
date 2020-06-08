cmake_minimum_required(VERSION 3.0)

set(LIB_NAME graphical_interface_models)
# QT5
# # Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

project(${LIB_NAME} CXX)

add_subdirectory(ut)

set(SRCS
	src/BookSeriesModel.cpp
	src/CategoryModel.cpp
	src/PersonModel.cpp
    )

set(HEADERS
	include/Models/BookSeriesModel.hpp
	include/Models/CategoryModel.hpp
	include/Models/PersonModel.hpp
	)

add_library(${LIB_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${LIB_NAME}
	PUBLIC
		Qt5::Widgets
		utils
		entity_types
	)

target_include_directories(${LIB_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
        src
	)