cmake_minimum_required(VERSION 3.0)

set(LIB_NAME graphical_interface)
# QT5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# # Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

project(${LIB_NAME} CXX)

set(SRCS
	src/MainWindow.cpp
    )

set(HEADERS
    include/GraphicalInterface/MainWindow.hpp
    include/GraphicalInterface/BookPage.hpp)

add_library(${LIB_NAME} ${SRCS})

target_link_libraries(${LIB_NAME}
	PUBLIC
        Qt5::Widgets)

target_include_directories(${LIB_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
        src
	)