#pragma once
#include <string>
#include <memory>
#include <vector>
#include <ctime>
#include <optional>
#include "BookStatus.h"

class Person;
class Category;
class Publisher;

namespace BookManager
{
	namespace Book
	{
		class Book
		{
		public:
			Book(std::string title, std::vector<std::shared_ptr<Person>> author) : title{title}, author{author} {}

			/* getter and setter */
		private:
			std::string title;
			std::vector<std::shared_ptr<Person>> author;
			std::shared_ptr<Category> category;
			std::shared_ptr<Publisher> editor;
			std::optional<std::time_t> published;
			std::optional<std::time_t> purchasedDate;
			std::optional<float> price;

			BookStatus status{ BookStatus::Listed };
			bool isRead{ false };
			std::optional<std::time_t> startReadingDate;
			std::optional<std::time_t> endReadingDate;
			int rate{ 0 };
			

		};
	} // namespace Book
} // namespace BookManager
