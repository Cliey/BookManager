cmake_minimum_required(VERSION 3.0)

set(LIB_NAME graphical_interface_popup)
# QT5
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# # Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

project(${LIB_NAME} CXX)

set(SRCS
	src/AuthorDialog.cpp
	src/CategoryDialog.cpp
	src/SettingsDialog.cpp
    )

set(HEADERS
    include/Popup/AuthorDialog.hpp
    include/Popup/CategoryDialog.hpp
    include/Popup/SettingsDialog.hpp
    )

add_library(${LIB_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${LIB_NAME}
	PUBLIC
		Qt5::Widgets
	PRIVATE
		managers
        entity::types
		)

target_include_directories(${LIB_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
        src
	)