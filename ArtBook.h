#pragma once
#include "Book.h"


namespace BookManager
{
	namespace Book
	{
		class Artbook : public Abstraction::Book
		{
		public:
			Artbook(std::string title, std::shared_ptr<Entity::Person> author_) : Book(title, author_) {}
			Artbook(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : Book(title, author) {}
			~Artbook() = default;

		private:


		};
	} // namespace Book
} // namespace BookManager