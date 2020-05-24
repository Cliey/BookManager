cmake_minimum_required(VERSION 3.0)

set(LIB_NAME graphical_interface_models)
# QT5
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# # Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

project(${LIB_NAME} CXX)

add_subdirectory(ut)

set(SRCS
	src/CategoryModel.cpp
    )

set(HEADERS
	include/Models/CategoryModel.hpp
	)

add_library(${LIB_NAME} ${SRCS})

target_link_libraries(${LIB_NAME}
	PUBLIC
		Qt5::Widgets
		utils
	PRIVATE
	)

target_include_directories(${LIB_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
        src
	)