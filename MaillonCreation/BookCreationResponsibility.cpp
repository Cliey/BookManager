#include <memory>
#include <iostream>
#include "BookCreationResponsibility.hpp"
#include "../Utils/Utils.hpp"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			BookCreationResponsibility::BookCreationResponsibility()
			{
			}

			BookCreationResponsibility::BookCreationResponsibility(std::unique_ptr<BookCreationResponsibility>&& next)
				: next(std::move(next))
			{
			}

			std::shared_ptr<Abstraction::Book> BookCreationResponsibility::handle(const BookType& context)
			{
				if (this->canHandle(context))
				{
					std::cout << "OK " << ::Utils::EnumUtils::bookTypeString(context) << std::endl;
					return this->createBook(context);
				}
				else if (this->next != nullptr)
				{
					std::cout << "Next" << std::endl;
					return this->next->handle(context);
				}
				else
				{
					std::cout << "Empty" << std::endl;
					return std::shared_ptr<Abstraction::Book>();
				}
			}

			void BookCreationResponsibility::append(std::unique_ptr<Utils::BookCreationResponsibility>&& maillon)
			{
				if (this->next == nullptr)
				{
					next = std::move(maillon);
				}
				else
				{
					this->next->append(std::forward<std::unique_ptr<Utils::BookCreationResponsibility>>(maillon));
				}
			}
		} // namespace Utils
	} // namespace Book
} // namespace BookManager