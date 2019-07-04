#include <iostream>
#include <string>
#include "Book.h"
#include "Person.h"
#include "Role.h"
#include "Publisher.h"
#include "Utils.h"

int main()
{
	std::cout << "Hello World" << std::endl;
	std::string a{ "Aello" };
	std::string b{ "Hello" };
	std::cout << "compare Hello & World : " << a.compare(b) << std::endl;
	Publisher p{ "haRaps" }, p2{ "haraps" };
	std::cout << "publisher = " << p2.getName() << std::endl;
	std::cout << "p1==p2 = " << std::boolalpha << (p == p2) << std::endl;
	p2.setName("j'ai lu");
	std::cout << "publisher = " << p2.getName() << std::endl;

	Entity::Person auth{ "emMAnuel", "Quentin" }, auth2{ "JK", "Rowling", Entity::Role::Author};
	//std::cout << "author = " << auth.getFullName() << std::endl;
	std::cout << "auth<auth2 = " << std::boolalpha << (auth < auth2) << std::endl;
	std::cout << "Auth = " << Utils::EnumUtils::roleString(auth.getRole()) <<
		" && Auth2 Role = " << Utils::EnumUtils::roleString(auth2.getRole()) << std::endl;
	Entity::Person auth3{ "JK", "Rowling", Entity::Role::Illustrator };
	std::cout << "auth2 == auth3 = " << std::boolalpha << (auth2 == auth3) << std::endl;
	
	std::cout << "Auth = " << auth.getFirstName() << std::endl;
	auth.setFirstName("jeAn");
	std::cout << "Auth = " << auth.getFirstName() << std::endl;

	/*
	Publisher p1{ "abc" }, p2{ "abe" }, p3{ "abb" };

	EXPECT_EQ(p1, "Abc");
	*/
	return 0;
}