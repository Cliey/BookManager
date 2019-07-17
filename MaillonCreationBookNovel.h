#pragma once

#pragma once
#include <memory>
#include <vector>
#include "BookFactory.h"
#include "BookCreationResponsibility.h"
#include "Novel.h"

namespace BookManager
{
	namespace Book
	{
		namespace Utils
		{
		class MaillonCreationBookNovel : public BookCreationResponsibility
		{
		private:
			class MaillonRegister {
			public:
				MaillonRegister() {
					BookManager::Book::BookFactory::append(std::make_unique<MaillonCreationBookNovel>());
				}
			};

			static MaillonRegister maillonRegister;
		public:
			template <typename ...Ts>
			MaillonCreationBookNovel(Ts&& ...args)
				: BookCreationResponsibility(std::forward<Ts>(args)...) {}

			BookType getContext() const override {
				return BookType::Novel;
			}

		protected:
			virtual std::shared_ptr<Abstraction::Book> createBook(const BookType& context) override final {
				return std::make_shared<Book::Novel>();
			}

		};
		} // namespace Utils
	} // namespace Book
} // namespace BookManager