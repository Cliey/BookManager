#pragma once
#include "./Abstract/Book.hpp"

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
	} // namespace Book
} // namespace BookManager