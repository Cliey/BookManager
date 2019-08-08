#pragma once

#pragma once
#include <memory>
#include <vector>
#include "../Book/Factory/BookFactory.hpp"
#include "BookCreationResponsibility.hpp"
#include "../Book/Comics.hpp"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			class MaillonCreationBookComics final : public BookCreationResponsibility
			{
			public:
				template <typename ...Ts>
				MaillonCreationBookComics(Ts&& ...args)
					: BookCreationResponsibility(std::forward<Ts>(args)...) {}

				BookType getContext() const override {
					return BookType::Comics;
				}

			protected:
				std::shared_ptr<Abstraction::Book> createBook(const BookType& context) final {
					return std::make_shared<Book::Comics>();
				}

			};
		} // namespace Utils
	} // namespace Book
} // namespace BookManager#pragma once
