#pragma once
#include <string>
#include "Utils.h"
#include "Role.h"

namespace Entity
{
	class Person
	{
	public:

		Person(std::string firstName_, std::string lastName_)
		{
			firstName = Utils::StringUtils::lowerCaseExceptFirstLetter(firstName_);
			lastName = Utils::StringUtils::lowerCaseExceptFirstLetter(lastName_);
			role = Role::Undefined;
		}

		Person(std::string firstName_, std::string lastName_, Role role_)
		{
			firstName = Utils::StringUtils::lowerCaseExceptFirstLetter(firstName_);
			lastName = Utils::StringUtils::lowerCaseExceptFirstLetter(lastName_);
			role = role_;
		}

		const std::string getFirstName() const { return this->firstName; }
		const std::string getLastName() const { return this->lastName; }
		const Role getRole() const { return this->role; }

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
	
	private:
		std::string getFullName()
		{
			std::string fullName{ lastName };
			fullName.append(" ");
			fullName.append(firstName);
			return fullName;
		}
		/*std::string getFullName()
		{
			std::string fullName{ lastName };
			fullName.append(" ");
			fullName.append(firstName);
			return fullName;
		}*/
		std::string firstName;
		std::string lastName;
		Role role;
	};
} // namespace Person