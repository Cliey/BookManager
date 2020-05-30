#pragma once
#include <string>
#include <memory>
#include <vector>
#include <ctime>
#include <optional>
#include "BookEnum/BookStatus.hpp"
#include "BookEnum/BookType.hpp"



class SubCategory;

namespace BookManager
{
	namespace Category
	{
		class Category;
	} // namespace Category

	namespace Entity
	{
		class BookSeries;
		class Person;
		class Publisher;
	} // namespace Entity
	namespace Book
	{
		namespace Abstraction
		{
			struct GeneralInfo
			{
				std::string title;
				std::vector<std::shared_ptr<Entity::Person>> author;
				std::shared_ptr<BookManager::Entity::BookSeries> bookSeries;
				std::shared_ptr<Entity::Publisher> publisher;
				std::optional<std::time_t> published;
			};

			struct CategoryInfo
			{
				std::shared_ptr<Category::Category> mainCategory;
				std::vector<std::shared_ptr<Category::Category>> subCategory;
			};

			struct StatisticsInfo
			{
				std::optional<double> price;
				std::optional<std::time_t> startReadingDate;
				std::optional<std::time_t> endReadingDate;
				std::optional<std::time_t> purchasedDate;
			};

			struct AdditionalInfo
			{
				BookStatus status{ BookStatus::Listed };
				bool isRead{ false };
				std::optional<int> rate;
				std::string comment;
			};

			struct Book
			{
			public:
				Book() = default;
				Book(std::string title, std::shared_ptr<Entity::Person> author_)
				{
					generalInfo.title = title;
					generalInfo.author.push_back(author_);
				}
				Book(std::string title, std::vector<std::shared_ptr<Entity::Person>> author)
				{
					generalInfo.title = title;
					generalInfo.author = author;
				}
				virtual ~Book() = 0;

				virtual BookManager:: Book::BookType getType() = 0;

				int id; //const

				GeneralInfo generalInfo;
				CategoryInfo categoryInfo;
				StatisticsInfo statInfo;
				AdditionalInfo additionalInfo;
			};
		} // namespace Abstraction
	} // namespace Book
} // namespace BookManager
