cmake_minimum_required(VERSION 3.0)

set(LIB_NAME maillon_creation)
project(${LIB_NAME} CXX)

set(SRCS
	src/BookCreationResponsibility.cpp
    )

set(HEADERS
	include/MaillonCreation/BookCreationResponsibility.hpp
	include/MaillonCreation/MaillonCreationBookArtBook.hpp
	include/MaillonCreation/MaillonCreationBookComics.hpp
	include/MaillonCreation/MaillonCreationBookManga.hpp
    include/MaillonCreation/MaillonCreationBookNovel.hpp
    )

add_library(${LIB_NAME} ${SRCS})
# add_library(creation::maillon_creation ALIAS ${LIB_NAME)

target_link_libraries(${LIB_NAME}
	PUBLIC
		book::types
		book::factory
		utils)

target_include_directories(${LIB_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	)