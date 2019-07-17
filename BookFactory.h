#pragma once
#include <memory>
#include <vector>
#include "BookType.h"
#include "BookCreationResponsibility.h"

namespace BookManager
{
	namespace Book
	{
		namespace Abstraction
		{
			class Book;
		} // namespace Abstraction
		class BookFactory
		{
		public:
			BookFactory() = delete;
			static Abstraction::Book& create(BookType type) {
					
			}

			static std::vector<BookType> getTypes()
			{
				return *contexts;
			}

			static void append(std::unique_ptr<Utils::BookCreationResponsibility>&& maillon)
			{
				if (firstItem == nullptr)
				{
					firstItem = std::move(maillon);
				}
				else
				{
					firstItem->append(std::forward<std::unique_ptr<Utils::BookCreationResponsibility>>(maillon));
				}
			}
		private:
			static std::unique_ptr<Utils::BookCreationResponsibility> firstItem;
			static std::unique_ptr<std::vector<BookType>> contexts;
		};
	} // namespace Book
} // namespace BookManager