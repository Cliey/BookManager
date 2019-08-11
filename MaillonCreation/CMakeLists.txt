cmake_minimum_required(VERSION 3.0)

project(maillon_creation CXX)

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

add_library(maillon_creation ${SRCS} ${HEADERS})
target_link_libraries(maillon_creation book book_factory)
target_include_directories(maillon_creation PUBLIC .)
