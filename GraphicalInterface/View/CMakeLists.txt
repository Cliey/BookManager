cmake_minimum_required(VERSION 3.0)

set(LIB_NAME graphical_interface_view)
# QT5
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# # Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

project(${LIB_NAME} CXX)

set(SRCS
	src/MainWindow.cpp
	src/BookPage.cpp
	src/BookSeriesPage.cpp
	src/CategoryPage.cpp
	src/PersonPage.cpp
    )

set(HEADERS
    include/View/MainWindow.hpp
    include/View/BookPage.hpp
    include/View/BookSeriesPage.hpp
    include/View/CategoryPage.hpp
    include/View/PersonPage.hpp)

add_subdirectory(Popup)

qt5_add_resources (SRCS resource.qrc)

add_library(${LIB_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${LIB_NAME}
	PUBLIC
		Qt5::Widgets
	PRIVATE
		graphical_interface_models
		graphical_interface_popup
		managers)

target_include_directories(${LIB_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
        src
	)