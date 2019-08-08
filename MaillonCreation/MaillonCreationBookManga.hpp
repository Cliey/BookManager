#pragma once
#include <memory>
#include <vector>
#include "../Book/Factory/BookFactory.hpp"
#include "BookCreationResponsibility.hpp"
#include "../Book/Manga.hpp"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			class MaillonCreationBookManga : public BookCreationResponsibility
			{
			public:
				template <typename ...Ts>
				MaillonCreationBookManga(Ts&& ...args)
					: BookCreationResponsibility(std::forward<Ts>(args)...) {}

				BookType getContext() const override {
					return BookType::Manga;
				}

			protected:
				std::shared_ptr<Abstraction::Book> createBook(const BookType& context) final {
					return std::make_shared<Book::Manga>();
				}

			};
		} // namespace Utils
	} // namespace Book
} // namespace BookManager#pragma once
