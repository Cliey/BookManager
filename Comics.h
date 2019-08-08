#pragma once
#include "BookFactory.h"
#include "DrawBook.h"
#include "BookCreationResponsibility.h"

namespace BookManager
{
	namespace Book
	{
		class Comics : public Abstraction::DrawBook
		{
		public:
			Comics() = default;
			Comics(std::string title, std::shared_ptr<Entity::Person> author_) : DrawBook(title, author_) {}
			Comics(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : DrawBook(title, author) {}
			~Comics() = default;

		private:


		};

		class MaillonCreationBookComics final : public Utils::BookCreationResponsibility
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
				std::shared_ptr<Abstraction::Book> createBook(const BookType& context) final {
					return std::make_shared<Book::Comics>();
				}

			};
	} // namespace Book
} // namespace BookManager#pragma once
