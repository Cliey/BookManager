#pragma once

namespace BookManager
{
    namespace Manager
    {
        class Manager
        {
        public:
            Manager() = default;
            void startApp();
        private:
            void registerHandlerFactory();
            void loadOption();

        };
    } // namespace Manager
} // namespace BookManager