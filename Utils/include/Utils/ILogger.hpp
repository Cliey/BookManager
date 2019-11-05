#pragma once
#include <string>
#include <fmt/format.h>

namespace Utils
{
    namespace Loggers
    {
        class ILogger
        {
            public:
                ILogger() = default;
                ~ILogger() = default;

                template<typename... Args>
                void log(const char* format, Args... args)
                {
                    fmt::memory_buffer out;
                    fmt::format_to(out, format, args...);

                    this->write(to_string(out));
                }

                ILogger& log() { return *this; }

                template <class T> ILogger& operator <<(const T& toLog)
                {
                    std::ostringstream stream;
                    stream << toLog;
                    this->write(stream.str());

                    return log();
                }

            private:
                virtual void write(const std::string& str) = 0;
        };
    } // namespace Loggers
} // namespace Utils
