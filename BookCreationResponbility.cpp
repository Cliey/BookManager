#include <memory>
#include "BookCreationResponsibility.h"

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
					return this->createBook(context);
				else if (this->next != nullptr)
					return this->next->createBook(context);
				else
					return std::shared_ptr<Abstraction::Book>();
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