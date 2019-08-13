#pragma once
#include "BookAbstract/Book.hpp"


namespace BookManager
{
	namespace Book
	{
		namespace Abstraction
		{
			class DrawBook : public Book
			{
			public:
				DrawBook() = default;
				DrawBook(std::string title, std::shared_ptr<Entity::Person> author_) : Book(title, author_) {}
				DrawBook(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : Book(title, author) {}
				virtual ~DrawBook() = 0;

				std::vector<std::shared_ptr<Entity::Person>> getIllustrator() { return this->illustrator; }

			private:
				std::vector<std::shared_ptr<Entity::Person>> illustrator;

			};
		} // namespace Abstraction
	} // namespace Book
} // namespace BookManager