#include "Utils/EnumUtils.hpp"
#include "BookEnum/BookStatus.hpp"
#include "BookEnum/BookType.hpp"
#include "EntityEnum/Role.hpp"

namespace Utils
{
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

