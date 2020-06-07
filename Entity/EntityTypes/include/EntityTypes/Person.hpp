#pragma once
#include <string>
#include "Utils/StringUtils.hpp"
#include "EntityEnum/Role.hpp"

namespace BookManager
{
	namespace Entity
	{
		class Person
		{
		public:
			Person() = default;
			Person(int id_, std::string firstName_, std::string lastName_)
			{
				id = id_;
				firstName = Utils::StringUtils::lowerCaseExceptFirstLetter(firstName_);
				lastName = Utils::StringUtils::lowerCaseExceptFirstLetter(lastName_);
				role = Role::Undefined;
			}

			Person(int id_, std::string firstName_, std::string lastName_, Role role_)
			{
				id = id_;
				firstName = Utils::StringUtils::lowerCaseExceptFirstLetter(firstName_);
				lastName = Utils::StringUtils::lowerCaseExceptFirstLetter(lastName_);
				role = role_;
			}

			Person& operator=(const Person& person)
			{
				this->id = person.id;
				this->firstName = person.firstName;
				this->lastName = person.lastName;
				this->role = person.role;
				return *this;
			}


			const int getId() const { return this->id; }
			const std::string getFirstName() const { return this->firstName; }
			const std::string getLastName() const { return this->lastName; }
			const Role getRole() const { return this->role; }

			void setId(int id) { this->id = id; }
			void setFirstName(std::string firstName) { this->firstName = Utils::StringUtils::lowerCaseExceptFirstLetter(firstName); }
			void setLastName(std::string firstName) { this->lastName = Utils::StringUtils::lowerCaseExceptFirstLetter(lastName); }
			void setRole(Role role) { this->role = role; }

			bool operator<(Person& rhs)
			{
				if ((this->getFullName()).compare(rhs.getFullName()) < 0)
					return true;
				return false;
			}

			bool operator==(Person& rhs)
			{
				if ((this->getFullName()).compare(rhs.getFullName()) == 0)
					return true;
				return false;
			}

			bool operator==(const int& rhs)
			{
				return (this->id == rhs);
			}

			const std::string getFullName() const
			{
				std::string fullName{ lastName };
				fullName.append(", ");
				fullName.append(firstName);
				return fullName;
			}
		private:
			int id;
			std::string firstName;
			std::string lastName;
			Role role;
		};
	} // namespace Entity
} // namespace BookManager