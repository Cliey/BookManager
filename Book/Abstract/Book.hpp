#pragma once
#include <string>
#include <memory>
#include <vector>
#include <ctime>
#include <optional>
#include "../Enum/BookStatus.hpp"



class SubCategory;

namespace BookManager
{
	namespace Category
	{
		class Category;
	} // namespace Category
	namespace Entity
	{
		class Person;
		class Publisher;
	} // namespace Entity
	namespace Book
	{
		namespace Abstraction
		{
			class Book
			{
			public:
				Book() = default;
				Book(std::string title, std::shared_ptr<Entity::Person> author_) : title{ title } {
					author.push_back(author_);
				}
				Book(std::string title, std::vector<std::shared_ptr<Entity::Person>> author) : title{ title }, author{ author } {}
				virtual ~Book() = 0;

				/* getter and setter */
				std::string getTitle() { return this->title; }
				std::vector<std::shared_ptr<Entity::Person>> getAuthor() { return this->author; }

			private:
				std::string title;
				std::vector<std::shared_ptr<Entity::Person>> author;

				std::shared_ptr<Category::Category> category;
				std::vector<std::weak_ptr<SubCategory>> subCategory;

				std::shared_ptr<Entity::Publisher> publisher;
				std::optional<std::time_t> published;
				std::optional<std::time_t> purchasedDate;
				std::optional<float> price;

				BookStatus status{ BookStatus::Listed };
				bool isRead{ false };
				std::optional<std::time_t> startReadingDate;
				std::optional<std::time_t> endReadingDate;
				int rate{ 0 };


			};
		} // namespace Abstraction
	} // namespace Book
} // namespace BookManager
