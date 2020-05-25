#pragma once
#include <exception>
#include <string>
#include <sstream>
#include <functional>

#define ADD_EXCEPTION(name_, id_) class E_##name_ : public Utils::Exceptions::Exception { \
    public: \
        E_##name_(const std::string str) : Exception(id_, #name_, str){} \
    } \

#define ADD_EXCEPTION_CALLBACK(name_, id_ ) class EC_##name_ : public Utils::Exceptions::ExceptionWithCallBack { \
    public: \
        EC_##name_(const std::string str, std::function<void()> callback) : ExceptionWithCallBack(id_, #name_, str, callback){} \
    } \

namespace Utils
{
	namespace Exceptions
	{
        class Exception : public std::exception
        {
        public:
            virtual const char* what() const throw()
            {
                std::stringstream errorStr;
                errorStr << "[Exception." << id << "." << name << "] : " << exceptionStr;
                return errorStr.str().c_str();
            }

        protected:
            Exception(int id, const char* name, const std::string exceptionStr) :
                id(id),
                name(name),
                exceptionStr(exceptionStr)
            {}

            int id;
            const char* name;
            const std::string exceptionStr;
        };

        class ExceptionWithCallBack : public Exception
        {
        public:
            const void executeCallback() const
            {
                this->callback();
            }
        protected:
            ExceptionWithCallBack(int id, const char* name, const std::string exceptionStr, std::function<void()> callback) :
                Exception(id, name, exceptionStr),
                callback(std::move(callback))
            {}

        private:
            std::function<void()> callback;
        };

        ADD_EXCEPTION(TypeError, 1);
        ADD_EXCEPTION(FieldNotFound, 2);
        ADD_EXCEPTION_CALLBACK(ForeignKeyFound, 3);
    }
}