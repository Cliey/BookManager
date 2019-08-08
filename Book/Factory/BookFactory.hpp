#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../../MaillonCreation/BookCreationResponsibility.hpp"
#include "../Abstract/Book.hpp"
#include "../Enum/BookType.hpp"

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
				std::cout << "hello" << std::endl;
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