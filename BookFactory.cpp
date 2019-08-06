#include "BookFactory.h"

using namespace BookManager::Book;

std::unique_ptr<Utils::BookCreationResponsibility> BookFactory::firstItem;
std::unique_ptr <std::vector<BookType>> BookFactory::contexts = std::make_unique< std::vector<BookType>>();
