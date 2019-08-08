#pragma once
#include "BookFactory.h"
#include "Book.h"
#include "BookCreationResponsibility.h"


namespace BookManager
{
	namespace Book
	{
		class Artbook : public Abstraction::Book
		{
		public:
			Artbook() = default;
			Artbook(std::string title, std::shared_ptr<Entity::Person> author_) : Book(title, author_) {}
			Artbook(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : Book(title, author) {}
			~Artbook() = default;

		private:


		};

		class MaillonCreationBookArtBook final : public Utils::BookCreationResponsibility
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
				std::shared_ptr<Abstraction::Book> createBook(const BookType& context) final {
					return std::make_shared<Book::Artbook>();
				}

			};
	} // namespace Book
} // namespace BookManager