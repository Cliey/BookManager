#pragma once
#include <memory>
#include <vector>
#include "BookFactory.h"
#include "BookCreationResponsibility.h"
#include "ArtBook.h"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			class MaillonCreationBookArtBook final : public BookCreationResponsibility
			{
			private:
				class MaillonRegister {
				public:
					MaillonRegister() {
						BookManager::Book::BookFactory::append(std::make_unique<MaillonCreationBookArtBook>());
					}
				};

				static MaillonRegister maillonRegister;

			public:
				template <typename ...Ts>
				MaillonCreationBookArtBook(Ts&& ...args)
					: BookCreationResponsibility(std::forward<Ts>(args)...) {}

				BookType getContext() const override {
					return BookType::ArtBook;
				}

			protected:
				virtual std::shared_ptr<Abstraction::Book> createBook(const BookType& context) override final {
					return std::make_shared<Book::Artbook>();
				}

			};
		} // namespace Utils
	} // namespace Book
} // namespace BookManager#pragma once
