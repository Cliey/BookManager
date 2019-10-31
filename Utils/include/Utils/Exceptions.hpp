#pragma once
#include <exception>
#include <string>
#include <sstream>

#define ADD_EXCEPTION(name_, id_) class E_##name_ : public Utils::Exceptions::Exception { \
    public: \
        E_##name_(const std::string str) : Exception(id_, #name_, str){} \
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

        private:
                int id;
                const char* name;
                const std::string exceptionStr;
        };

        ADD_EXCEPTION(TypeError, 1);
        ADD_EXCEPTION(FieldNotFound, 2);
    }
}