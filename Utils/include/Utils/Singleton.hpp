#pragma once
#include <memory>

namespace Utils
{
    template <typename T>
    class Singleton
    {
        public:
            static std::shared_ptr<T> getinstance()
            {
                static std::shared_ptr<T> instance = nullptr;
                if(!instance)
                    instance.reset(new T());
                return instance;
            }

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        protected:
            virtual ~Singleton() {}
            Singleton() {}

    };
} //namespace Utils