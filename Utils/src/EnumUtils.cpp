#include "Utils/EnumUtils.hpp"
#include "BookEnum/BookStatus.hpp"
#include "BookEnum/BookType.hpp"
#include "EntityEnum/Role.hpp"
#include "Managers/Utils/SortingEnum.hpp"
#include "Managers/Utils/SettingsEnum.hpp"

namespace Utils
{
	namespace EnumUtils
	{
		std::string roleString(BookManager::Entity::Role role)
		{
			using namespace BookManager::Entity;
			switch (role)
			{
				case Role::Author:
					return "Author";
				case Role::Illustrator:
					return "Illustrator";
				case Role::Undefined:
				default:
					return "Undefined";
			}
		}

		std::string bookStatusString(BookManager::Book::BookStatus status)
		{
			using namespace BookManager::Book;
			switch (status)
			{
				case BookStatus::HaveIt:
					return "HaveIt";
				case BookStatus::Listed:
					return "Listed";
				case BookStatus::WantIt:
					return "WantIt";
				default:
					return "Undefined";
			}
		}

		std::string bookTypeString(BookManager::Book::BookType type)
		{
			using namespace BookManager::Book;
			switch (type)
			{
			case BookType::ArtBook:
				return "ArtBook";
			case BookType::Comics:
				return "Comics";
			case BookType::Manga:
				return "Manga";
			case BookType::Novel:
				return "Novel";
			default:
				return "Undefined";
			}
		}

		std::string sortingEnumBookString(BookManager::Manager::Enum::SortingEnumBook sort)
		{
			using namespace BookManager::Manager::Enum;
			switch(sort)
			{
				case SortingEnumBook::authorName_desc :
					return "authorName_desc";
				case SortingEnumBook::authorName_asc :
					return "authorName_asc";
                case SortingEnumBook::price_desc :
					return "price_desc";
				case SortingEnumBook::price_asc :
					return "price_asc";
                case SortingEnumBook::title_desc :
					return "title_desc";
				case SortingEnumBook::title_asc :
					return "title_asc";
                case SortingEnumBook::dateAdded_desc :
					return "dateAdded_desc";
				case SortingEnumBook::dateAdded_asc :
					return "dateAdded_asc";
                case SortingEnumBook::datePublished_desc :
					return "datePublished_desc";
				case SortingEnumBook::datePublished_asc :
					return "datePublished_asc";
				case SortingEnumBook::undefined :
				default:
					return "Undefined";
			}
		}

		std::string displayTypeEnumString(BookManager::Manager::Enum::DisplayBookEnum displayType)
		{
			using namespace BookManager::Manager::Enum;
			switch(displayType)
			{
				case DisplayBookEnum::listView :
					return "listView";
				case DisplayBookEnum::coverView :
					return "coverView";
				case DisplayBookEnum::bookshelfView :
					return "bookshelfView";
				case DisplayBookEnum::undefined :
				default:
					return "Undefined";
			}
		}

	} // namespace EnumUtils
} // namespace Utils

