cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER /cygdrive/c/cygwin64/bin/g++.exe --std=c++1z)
#set(CMAKE_C_COMPILER_WORKS 1)
#set(CMAKE_CXX_COMPILER_WORKS 1)

# Project Name
project(BookManager)

set(SRCS
	BookCreationResponbility.cpp
	MaillonCreationBookArtBook.cpp
	MaillonCreationBookComics.cpp
	MaillonCreationBookManga.cpp
	MaillonCreationBookNovel.cpp
	Book.cpp
	DrawBook.cpp
	Utils.cpp
	main.cpp
	BookFactory.cpp
    )

set(HEADERS
	BookCreationResponsibility.h
    ArtBook.h
	Book.h
	BookStatus.h
	BookType.h
	Category.h
	Comics.h
	DrawBook.h
	Editor.h
	MaillonCreationBookArtBook.h
	MaillonCreationBookComics.h
	MaillonCreationBookManga.h
	MaillonCreationBookNovel.h
	Manga.h
	Novel.h
	Person.h
	Publisher.h
	Role.h
	Utils.h
	BookFactory.h
    )

# Exectuable name is Bookmmanager, compiled from files stored in SRCS and HEADERS
add_executable(BookManager ${SRCS} ${HEADERS})
