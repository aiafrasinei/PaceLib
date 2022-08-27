#include "ConLog.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>


std::string ConLog::format = "%c %Z";

void ConLog::SetTimeFormat(std::string format)
{
    ConLog::format = format;
}

void ConLog::Info(std::string message)
{    
    time_t t = time(NULL);
    std::tm tm = *std::localtime(&t);
    std::cout <<  " INFO" << " [" << std::put_time(&tm, format.c_str()) << "]" << " - " + message << std::endl;
}

void ConLog::Warn(std::string message)
{
    time_t t = time(NULL);
    std::tm tm = *std::localtime(&t);
    std::cout << " WARNING" << " [" << std::put_time(&tm, format.c_str()) << "]" << " - " + message << std::endl;
}

void ConLog::Error(std::string message)
{
    time_t t = time(NULL);
    std::tm tm = *std::localtime(&t);;
    std::cout << " ERROR" << " [" << std::put_time(&tm, format.c_str()) << "]" << " - " + message << std::endl;
}

void ConLog::Custom(std::string level, std::string message)
{
    time_t t = time(NULL);
    std::tm tm = *std::localtime(&t);
    std::cout << " " << level << " [" << std::put_time(&tm, format.c_str()) << "]" << " - " + message << std::endl;
}
