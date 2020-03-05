#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Utils/StringUtils.hpp"

class SubCategory;
namespace BookManager
{
	namespace Category
	{
		class Category
		{
		public:
			Category(int id_, std::string name_) {
				id = id_;
				name = Utils::StringUtils::lowerCaseExceptFirstLetter(name_);
			}

			int getId() { return this->id; }
			std::string getName() { return this->name; }
			void setName(std::string name_) {
				this->name = Utils::StringUtils::lowerCaseExceptFirstLetter(name_);
			}

			bool operator<(const Category& rhs)
			{
				if ((this->name).compare(rhs.name) < 0)
					return true;
				return false;
			}
			bool operator==(const Category& rhs)
			{
				if ((this->name).compare(rhs.name) == 0)
					return true;
				return false;
			}
			//void addSubCategory();
		private:
			int id;
			std::string name;
			//std::vector<std::weak_ptr<SubCategory>> subcategoryList;
		};
	} // namespace Category
} // namespace BookManager