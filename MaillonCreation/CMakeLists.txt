cmake_minimum_required(VERSION 3.0)

set(LIB_NAME maillon_creation)
project(${LIB_NAME} CXX)

set(SRCS
	BookCreationResponsibility.cpp
    )

set(HEADERS
	BookCreationResponsibility.hpp
	MaillonCreationBookArtBook.hpp
	MaillonCreationBookComics.hpp
	MaillonCreationBookManga.hpp
    MaillonCreationBookNovel.hpp
    )

add_library(${LIB_NAME} ${SRCS} ${HEADERS})
target_link_libraries(${LIB_NAME} book book_factory)
target_include_directories(${LIB_NAME} PUBLIC .)
