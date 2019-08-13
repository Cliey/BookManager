#pragma once
#include <string>

namespace BookManager
{
	namespace Entity
	{
		enum class Role;
	} // namespace Entity

	namespace Book
	{
		enum class BookStatus;
		enum class BookType;
	} // namespace Book
} // namespace BookManager

namespace Utils
{
	namespace EnumUtils
	{
		std::string roleString(BookManager::Entity::Role);
		std::string bookStatusString(BookManager::Book::BookStatus);
		std::string bookTypeString(BookManager::Book::BookType);
	} // namespace EnumUtils
} // namespace Utils