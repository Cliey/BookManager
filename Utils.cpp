#include  "Utils.h"
#include <algorithm>
#include "Role.h"
#include "BookStatus.h"

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
		std::string roleString(Entity::Role role)
		{
			switch (role)
			{
				case Entity::Role::Author:
					return "Author";
				case Entity::Role::Illustrator:
					return "Illustrator";
				case Entity::Role::Undefined:
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
	} // namespace EnumUtils
} // namespace Utils

