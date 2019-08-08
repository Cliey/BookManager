#pragma once

#pragma once
#include <memory>
#include <vector>
#include "../Book/Factory/BookFactory.hpp"
#include "BookCreationResponsibility.hpp"
#include "../Book/Novel.hpp"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			class MaillonCreationBookNovel : public BookCreationResponsibility
			{
			public:
				template <typename ...Ts>
				MaillonCreationBookNovel(Ts&& ...args)
					: BookCreationResponsibility(std::forward<Ts>(args)...) {}

				BookType getContext() const override {
					return BookType::Novel;
				}

			protected:
				std::shared_ptr<Abstraction::Book> createBook(const BookType& context) final {
					return std::make_shared<Book::Novel>();
				}

			};
		} // namespace Utils
	} // namespace Book
} // namespace BookManager