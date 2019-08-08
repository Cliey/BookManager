#pragma once
#include <memory>
#include <vector>
#include "BookFactory.h"
#include "BookCreationResponsibility.h"
#include "Manga.h"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
			// class MaillonCreationBookManga : public BookCreationResponsibility
			// {
			// private:
			// 	class MaillonRegister {
			// 	public:
			// 		MaillonRegister() {
			// 			BookManager::Book::BookFactory::append(std::make_unique<MaillonCreationBookManga>());
			// 		}
			// 	};

			// 	static MaillonRegister maillonRegister;

			// public:
			// 	template <typename ...Ts>
			// 	MaillonCreationBookManga(Ts&& ...args)
			// 		: BookCreationResponsibility(std::forward<Ts>(args)...) {}

			// 	BookType getContext() const override {
			// 		return BookType::Manga;
			// 	}

			// protected:
			// 	virtual std::shared_ptr<Abstraction::Book> createBook(const BookType& context) override final {
			// 		return std::make_shared<Book::Manga>();
			// 	}

			// };
		} // namespace Utils
	} // namespace Book
} // namespace BookManager#pragma once
