#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "BookCreationResponsibility.h"
#include "Book.h"
#include "BookType.h"

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
		private:
			static std::unique_ptr<Utils::BookCreationResponsibility> firstItem;
			static std::unique_ptr<std::vector<BookType>> contexts;
		public:
			BookFactory() = delete;
			static void append(std::unique_ptr<Utils::BookCreationResponsibility>&& maillon)
			{
				contexts->push_back(maillon->getContext());
				if (firstItem == nullptr)
				{
					firstItem = std::move(maillon);
				}
				else
				{
					firstItem->append(std::forward<std::unique_ptr<Utils::BookCreationResponsibility>>(maillon));
				}
			}

			static std::shared_ptr<Abstraction::Book> create(BookType type) {
				 return firstItem->handle(type);
			}

			static const std::vector<BookType>& getTypes()
			{
				return *contexts;
			}



		};
	} // namespace Book
} // namespace BookManager