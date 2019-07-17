#pragma once
#include "Book.h"


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
	} // namespace Book
} // namespace BookManager
