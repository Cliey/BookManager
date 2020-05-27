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

	namespace Manager
	{
		namespace Enum
		{
			enum class SortingEnumBook : uint8_t;
			enum class DisplayBookEnum : uint8_t;
		} // namespace Enum
	} // namespace Managers
} // namespace BookManager

namespace Utils
{
	namespace EnumUtils
	{
		std::string roleString(BookManager::Entity::Role);
		std::string bookStatusString(BookManager::Book::BookStatus);
		std::string bookTypeString(BookManager::Book::BookType);
		std::string sortingEnumBookString(BookManager::Manager::Enum::SortingEnumBook);
		std::string displayTypeEnumString(BookManager::Manager::Enum::DisplayBookEnum);
	} // namespace EnumUtils
} // namespace Utils