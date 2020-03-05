#pragma once
#include <string>
#include "Utils/StringUtils.hpp"
namespace BookManager
{
	namespace Entity
	{

		class Publisher
		{
		public:
			Publisher(int id_, std::string name_){
				id = id_;
				name = Utils::StringUtils::lowerCaseExceptFirstLetter(name_);
			}

			std::string const getName() const { return this->name; }
			int const getId() const { return this->id; }

			void setName(std::string name) { this->name = Utils::StringUtils::lowerCaseExceptFirstLetter(name); }

			bool operator<(const Publisher& rhs)
			{
				if((this->name).compare(rhs.name) < 0)
					return true;
				return false;
			}

			bool operator==(const Publisher& rhs)
			{
				if ((this->name).compare(rhs.name) == 0)
					return true;
				return false;
			}
		private:
			int id;
			std::string name;
		};
	} // namespace Entity
} // namespace BookManager