#include "Utils/Loggers.hpp"
#include <iostream>

namespace Utils
{
    namespace Loggers
    {
        /*****************
         *****************
         * LoggerConsole *
         *****************
        ******************/

        void LoggerConsole::write(const std::string& str)
        {
            printf("[%s]", levelLog);
            printf(str.c_str());
        }

        /******************
         ******************
         *   LoggerFile   *
         ******************
        *******************/

        void LoggerFile::write(const std::string& str)
        {
            file << str;
        }

        LoggerFile::LoggerFile() : file("logs/Output.log")
        {
            file << "Starting Logging...\n";
        }

        /******************
         ******************
         *  LoggerWindow  *
         ******************
        *******************/

        void LoggerWindow::write(const std::string& str)
        {
            // PopUp a window
            printf("[%s]", levelLog);
            printf(str.c_str());
        }


    } // namespace Loggers
} // namespace Utils