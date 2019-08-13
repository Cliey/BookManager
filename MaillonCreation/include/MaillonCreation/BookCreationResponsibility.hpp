#pragma once
#include <memory>
#include <vector>
#include "BookEnum/BookType.hpp"
#include "BookAbstract/Book.hpp"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			class BookCreationResponsibility
			{
			public:

				BookCreationResponsibility();
				BookCreationResponsibility(std::unique_ptr<BookCreationResponsibility>&& next);
				std::shared_ptr<Abstraction::Book> handle(const BookType& context);
				virtual BookType getContext() const = 0;
				void append(std::unique_ptr<Utils::BookCreationResponsibility>&& maillon);
				virtual ~BookCreationResponsibility() = default;

			protected:
				virtual bool canHandle(const BookType& context) {
					return context == this->getContext();
				}
				virtual std::shared_ptr<Abstraction::Book> createBook(const BookType& context) = 0;
			private:
				std::unique_ptr<BookCreationResponsibility> next;
			};
		} // namespace Utils
	} // namespace Book
} // namespace BookManager