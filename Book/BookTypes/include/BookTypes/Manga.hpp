#pragma once
#include "BookAbstract/DrawBook.hpp"

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
	} // namespace Book
} // namespace BookManager#pragma once
