# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_COMPILER C:/cygwin64/bin/)
SET (CMAKE_C_COMPILER_WORKS 1)
SET (CMAKE_CXX_COMPILER_WORKS 1)
#set(CMAKE_C_COMPILER C:/cygwin64/bin/)

# Notre projet est étiqueté hello
project(BookManager)

# Crée des variables avec les fichiers à compiler
set(SRCS
	Book.cpp
	BookCreationResponbility.cpp
	BookFactory.cpp
	MaillonCreationBookArtBook.cpp
	DrawBook.cpp
	main.cpp
	MaillonCreationBookComics.cpp
	MaillonCreationBookManga.cpp
	MaillonCreationBookNovel.cpp
	Utils.cpp
    )
    
set(HEADERS
    ArtBook.h
	Book.h
	BookCreationResponsibility.h
	BookFactory.h
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
    )
	
# On indique que l'on veut un exécutable "hello" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(BookManager ${SRCS} ${HEADERS})