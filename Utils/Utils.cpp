#include  "Utils.hpp"
#include <algorithm>
#include "../Role.hpp"
#include "../Book/Enum/BookStatus.hpp"
#include "../Book/Enum/BookType.hpp"

namespace Utils
{
	namespace StringUtils
	{
		std::string lowerCaseExceptFirstLetter(const std::string& str)
		{
			std::string strModified{ str };
			std::transform(strModified.begin(), strModified.end(), strModified.begin(), ::tolower);
			strModified[0] = toupper(strModified[0]);
			return strModified;
		}
	} // namespace StringUtils

	namespace EnumUtils
	{
		std::string roleString(BookManager::Entity::Role role)
		{
			switch (role)
			{
				case BookManager::Entity::Role::Author:
					return "Author";
				case BookManager::Entity::Role::Illustrator:
					return "Illustrator";
				case BookManager::Entity::Role::Undefined:
				default:
					return "Undefined";
			}
		}

		std::string bookStatusString(BookManager::Book::BookStatus status)
		{
			switch (status)
			{
				case BookManager::Book::BookStatus::HaveIt:
					return "HaveIt";
				case BookManager::Book::BookStatus::Listed:
					return "Listed";
				case BookManager::Book::BookStatus::WantIt:
					return "WantIt";
				default:
					return "Undefined";
			}
		}

		std::string bookTypeString(BookManager::Book::BookType type)
		{
			switch (type)
			{
			case BookManager::Book::BookType::ArtBook:
				return "ArtBook";
			case BookManager::Book::BookType::Comics:
				return "Comics";
			case BookManager::Book::BookType::Manga:
				return "Manga";
			case BookManager::Book::BookType::Novel:
				return "Novel";
			default:
				return "Undefined";
			}
		}

	} // namespace EnumUtils
} // namespace Utils

