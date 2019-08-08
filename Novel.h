#pragma once
#include "BookFactory.h"
#include "Book.h"
#include "BookCreationResponsibility.h"


namespace BookManager
{
	namespace Book
	{
		class Novel : public Abstraction::Book
		{
		public:
			Novel() = default;
			Novel(std::string title, std::shared_ptr<Entity::Person> author_) : Book(title, author_) {}
			Novel(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : Book(title, author) {}
			~Novel() = default;

		private:


		};

		class MaillonCreationBookNovel : public Utils::BookCreationResponsibility
		{
		private:
			class MaillonRegister {
			public:
				MaillonRegister() {
					BookManager::Book::BookFactory::append(std::make_unique<MaillonCreationBookNovel>());
				}
			};

			static MaillonRegister maillonRegister;
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
	} // namespace Book
} // namespace BookManager
