#pragma once

#pragma once
#include <memory>
#include <vector>
#include "BookFactory.h"
#include "BookCreationResponsibility.h"
#include "Comics.h"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			class MaillonCreationBookComics final : public BookCreationResponsibility
			{
			private:
				class MaillonRegister {
				public:
					MaillonRegister() {
						BookManager::Book::BookFactory::append(std::make_unique<MaillonCreationBookComics>());
					}
				};
				
				static MaillonRegister maillonRegister;
				
			public:
				template <typename ...Ts>
				MaillonCreationBookComics(Ts&& ...args)
					: BookCreationResponsibility(std::forward<Ts>(args)...) {}

				BookType getContext() const override {
					return BookType::Comics;
				}

			protected:
				virtual std::shared_ptr<Abstraction::Book> createBook(const BookType& context) override final {
					return std::make_shared<Book::Comics>();
				}

			};
		} // namespace Utils
	} // namespace Book
} // namespace BookManager#pragma once
