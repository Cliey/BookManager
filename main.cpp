#include <iostream>
#include "View/MainWindow.hpp"
#include <QApplication>

void test()
{
	// BookManager::Manager::GeneralManager GeneralManager;
	// GeneralManager.startApp();
	// std::string a{ "Aello" };
	// std::string b{ "Hello" };
	// std::cout << "compare Hello & World : " << a.compare(b) << std::endl;
	// BookManager::Entity::Publisher p{ "haRaps" }, p2{ "haraps" };
	// std::cout << "publisher = " << p2.getName() << std::endl;
	// std::cout << "p1==p2 = " << std::boolalpha << (p == p2) << std::endl;
	// p2.setName("j'ai lu");
	// std::cout << "publisher = " << p2.getName() << std::endl;

	// BookManager::Entity::Person auth{ "emMAnuel", "Quentin" }, auth2{ "JK", "Rowling", BookManager::Entity::Role::Author };
	// //std::cout << "author = " << auth.getFullName() << std::endl;
	// std::cout << "auth<auth2 = " << std::boolalpha << (auth < auth2) << std::endl;
	// std::cout << "Auth = " << Utils::EnumUtils::roleString(auth.getRole()) <<
	// 	" && Auth2 Role = " << Utils::EnumUtils::roleString(auth2.getRole()) << std::endl;
	// BookManager::Entity::Person auth3{ "JK", "Rowling", BookManager::Entity::Role::Illustrator };
	// std::cout << "auth2 == auth3 = " << std::boolalpha << (auth2 == auth3) << std::endl;

	// std::cout << "Auth = " << auth.getFirstName() << std::endl;
	// auth.setFirstName("jeAn");
	// std::cout << "Auth = " << auth.getFirstName() << std::endl;

	// std::shared_ptr<BookManager::Entity::Person> JK = std::make_shared<BookManager::Entity::Person>("JK", "Rowling", BookManager::Entity::Role::Author);
	// BookManager::Book::Novel Harry{ "Harry Potter T.1", JK };
	// std::cout << "Book = " << Harry.getTitle() << ", written by " << Harry.getAuthor().at(0)->getFirstName() << std::endl;

	// std::shared_ptr<BookManager::Book::Artbook> Frozen = std::make_shared<BookManager::Book::Artbook>("Art Of Frozen", std::make_shared<BookManager::Entity::Person>(auth));
	// std::shared_ptr<BookManager::Book::Comics> Batman = std::make_shared<BookManager::Book::Comics>("Batman", std::make_shared<BookManager::Entity::Person>(auth));
	// std::shared_ptr<BookManager::Book::Manga> naruto = std::make_shared<BookManager::Book::Manga>("Naruto", JK);
	// //std::shared_ptr<BookManager::Book::DrawBook> dr = std::make_shared<BookManager::Book::DrawBook>("Draw", JK);

	// std::vector<std::shared_ptr<BookManager::Book::Abstraction::Book>> books;
	// books.push_back(std::make_shared<BookManager::Book::Novel>(Harry));
	// books.push_back(Frozen);
	// books.push_back(Batman);
	// books.push_back(naruto);
	// naruto->setTitle("Narr");
	// books.at(2)->setTitle("SuperMan");
	// std::cout << "List of books : " << std::endl;
	// for (auto book : books)
	// {
	// 	auto author = book->getAuthor().at(0);
	// 	std::cout << "Book = " << book->getTitle() << ", written by " << author->getLastName() << ", " << author->getFirstName() << std::endl;
	// }

	// std::cout << "Type of book : " << std::endl;
	// for (const BookManager::Book::BookType& type : BookManager::Book::BookFactory::getTypes())
	// {
	// 	std::cout << "- " << Utils::EnumUtils::bookTypeString(type) << std::endl;
	// }

	// std::shared_ptr<BookManager::Book::Abstraction::Book> newNovel = BookManager::Book::BookFactory::create(BookManager::Book::BookType::Comics);
}

int main(int argc, char *argv[])
{
	std::cout << "Hello World" << std::endl;

	QApplication app(argc, argv);
	MainWindow mainWindow;
	mainWindow.show();
    return app.exec();
}

