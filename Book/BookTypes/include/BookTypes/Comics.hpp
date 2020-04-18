#pragma once
#include "BookAbstract/DrawBook.hpp"

namespace BookManager
{
	namespace Book
	{
		struct Comics : public Abstraction::DrawBook
		{
		public:
			Comics() = default;
			Comics(std::string title, std::shared_ptr<Entity::Person> author_) : DrawBook(title, author_) {}
			Comics(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : DrawBook(title, author) {}
			~Comics() = default;

			BookManager::Book::BookType getType() override { return BookManager:: Book::BookType::Comics; }

		private:


		};
	} // namespace Book
} // namespace BookManager#pragma once
