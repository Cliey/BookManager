#pragma once
#include "DrawBook.h"


namespace BookManager
{
	namespace Book
	{
		class Comics : public Abstraction::DrawBook
		{
		public:
			Comics(std::string title, std::shared_ptr<Entity::Person> author_) : DrawBook(title, author_) {}
			Comics(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : DrawBook(title, author) {}
			~Comics() = default;

		private:


		};
	} // namespace Book
} // namespace BookManager#pragma once
