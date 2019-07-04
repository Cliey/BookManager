#pragma once
#include  <string>

namespace Entity
{
	enum class Role;
} // namespace Entity
namespace BookManager
{
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
		std::string roleString(Entity::Role);
		std::string bookStatusString(BookManager::Book::BookStatus);
	} // namespace EnumUtils
} // namespace Utils