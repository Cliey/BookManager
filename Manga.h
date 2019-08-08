#pragma once
#include "DrawBook.h"
#include "BookFactory.h"
#include "BookCreationResponsibility.h"

namespace BookManager
{
	namespace Book
	{
		class Manga : public Abstraction::DrawBook
		{
		public:
			Manga() = default;
			Manga(std::string title, std::shared_ptr<Entity::Person> author_) : DrawBook(title, author_) {}
			Manga(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : DrawBook(title, author) {}
			~Manga() = default;

		private:


		};

		class MaillonCreationBookManga : public Utils::BookCreationResponsibility
			{
			private:
				class MaillonRegister {
				public:
					MaillonRegister() {
						BookManager::Book::BookFactory::append(std::make_unique<MaillonCreationBookManga>());
					}
				};

				static MaillonRegister maillonRegister;

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
	} // namespace Book
} // namespace BookManager#pragma once
