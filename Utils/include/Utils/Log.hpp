#pragma once
#include "Utils/Loggers.hpp"

#define DEBUG_MODE
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_STRING(logLevel) "[" << #logLevel << "] " << __FILENAME__ << ":" << __LINE__ << " - "

#define LOG(logLevel, format, ...) {\
        std::ostringstream stri;\
        stri << LOG_STRING(logLevel) << format << "\n";\
        Utils::Loggers::LoggerConsole::getinstance()->log(stri.str().c_str(), ##__VA_ARGS__);\
        Utils::Loggers::LoggerFile::getinstance()->log(stri.str().c_str(), ##__VA_ARGS__);\
    }

#define LOG_INFO(format, ...) LOG(LOG_INFO, format, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) LOG(LOG_ERROR, format, ##__VA_ARGS__)

#ifndef UNIT_TESTS
#define LOG_WINDOW(format, ...) {\
        std::stringstream stri;\
        stri << LOG_STRING(LOG_WINDOW) << format << "\n";\
        Utils::Loggers::LoggerWindow::getinstance()->log(stri.str().c_str(), ##__VA_ARGS__);\
    }
#else
#define LOG_WINDOW(format, ...) {\
        std::stringstream stri;\
        stri << LOG_STRING(LOG_WINDOW_UT) << format << "\n";\
        Utils::Loggers::LoggerWindow::getinstance()->log(stri.str().c_str(), ##__VA_ARGS__);\
    }
#endif

#ifndef UNIT_TESTS
#define LOG_WINDOW_YES_NO(functionValid, format, ...) {\
        std::stringstream stri;\
        stri << LOG_STRING(LOG_WINDOW_YES_NO) << format << "\n";\
        Utils::Loggers::LoggerWindowYesNo::getinstance()->log(functionValid, stri.str().c_str(), ##__VA_ARGS__);\
    }
#else
#define LOG_WINDOW_YES_NO(functionValid, format, ...) {\
        std::stringstream stri;\
        stri << LOG_STRING(LOG_WINDOW_YES_NO_UT) << format << "\n";\
        Utils::Loggers::LoggerWindowYesNo::getinstance()->log([](){}, stri.str().c_str(), ##__VA_ARGS__);\
    }
#endif