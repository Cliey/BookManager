#pragma once
#include <memory>
#include <vector>
#include "../Book/Factory/BookFactory.hpp"
#include "BookCreationResponsibility.hpp"
#include "../Book/ArtBook.hpp"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			class MaillonCreationBookArtBook final : public BookCreationResponsibility
			{
			public:
				template <typename ...Ts>
				MaillonCreationBookArtBook(Ts&& ...args)
					: BookCreationResponsibility(std::forward<Ts>(args)...) {}

				BookType getContext() const override {
					return BookType::ArtBook;
				}

			protected:
				std::shared_ptr<Abstraction::Book> createBook(const BookType& context) final {
					return std::make_shared<Book::Artbook>();
				}

			};
		} // namespace Utils
	} // namespace Book
} // namespace BookManager#pragma once
