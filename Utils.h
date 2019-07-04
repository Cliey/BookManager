#pragma once
#include  <string>

namespace BookManager
{
	namespace Entity
	{
		enum class Role;
	} // namespace Entity

	namespace Book
	{
		enum class BookStatus;
	} // namespace Book
} // namespace BookManager

namespace Utils
{
	namespace StringUtils
	{
		std::string lowerCaseExceptFirstLetter(const std::string&);
	} // namespace StringUtils

	namespace EnumUtils
	{
		std::string roleString(BookManager::Entity::Role);
		std::string bookStatusString(BookManager::Book::BookStatus);
	} // namespace EnumUtils
} // namespace Utils