#pragma once
#include <fstream>
#include <sstream>
#include <functional>
#include "Utils/Singleton.hpp"
#include "Utils/ILogger.hpp"

namespace Utils
{
    namespace Loggers
    {
        class LoggerConsole : public ::Utils::Singleton<LoggerConsole>, public ILogger
        {
            friend class ::Utils::Singleton<LoggerConsole>;
            private:
                LoggerConsole() = default;
                virtual void write(const std::string& str) override;
                virtual void write(std::function<void()> functionValid, const std::string& str) override {}

            protected:
                const char* levelLog{"Console"};
        };

        class LoggerFile : public ::Utils::Singleton<LoggerFile>, public ILogger
        {
            friend class ::Utils::Singleton<LoggerFile>;
            public:
                ~LoggerFile() { file.close(); }
            private:
                LoggerFile();
                virtual void write(const std::string& str) override;
                virtual void write(std::function<void()> functionValid, const std::string& str) override {}

            protected:
                std::ofstream file;
        };

        class LoggerWindow : public ::Utils::Singleton<LoggerWindow>, public ILogger
        {
            friend class ::Utils::Singleton<LoggerWindow>;
            private:
                LoggerWindow() = default;
                virtual void write(const std::string& str) override;
                virtual void write(std::function<void()> functionValid, const std::string& str) override {}

            protected:
                const char* levelLog{"Window"};
        };

         class LoggerWindowYesNo : public ::Utils::Singleton<LoggerWindowYesNo>, public ILogger
        {
            friend class ::Utils::Singleton<LoggerWindowYesNo>;
            private:
                LoggerWindowYesNo() = default;
                virtual void write(const std::string& str) override{}
                virtual void write(std::function<void()> functionValid, const std::string& str) override;

            protected:
                const char* levelLog{"WindowYesNo"};
        };
    } // namespace Loggers
} // namespace Utils