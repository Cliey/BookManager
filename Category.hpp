#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Utils/StringUtils.hpp"

namespace BookManager
{
	namespace Category
	{
		class Category
		{
		public:
			Category() = default;

			Category(int id_, std::string name_) {
				id = id_;
				name = Utils::StringUtils::lowerCaseExceptFirstLetter(name_);
			}

			const int getId() const { return this->id; }
			const std::string getName() const { return this->name; }
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
		private:
			int id;
			std::string name;
		};
	} // namespace Category
} // namespace BookManager