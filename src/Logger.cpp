#include "Logger.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>

Logger::Logger(/* args */)
{
}

Logger::~Logger()
{
}

bool Logger::writeInFiles(std::string str)
{
    std::fstream fs;
    std::string path = getDate();

    fs.open(path, std::fstream::in | std::fstream::out | std::fstream::app);

    fs << getTime() << std::endl;
    fs << str << std::endl;
    fs << std::endl;

    fs.close();
    return true;
}

std::string Logger::getDate()
{
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    std::string res = "";
    
    res.append(std::to_string(local_time->tm_mday));
    res.append("-");
    res.append(std::to_string(local_time->tm_mon + 1));
    res.append("-");
    res.append(std::to_string(local_time->tm_year + 1900));
    return(res);
//    std::cout << "Year: "<< 1900 + local_time->tm_year << std::endl;
//    std::cout << "Month: "<< 1 + local_time->tm_mon<< std::endl;
//    std::cout << "Day: "<< local_time->tm_mday << std::endl;
//    std::cout << "Time: "<< local_time->tm_hour << ":" << local_time->tm_min << ":" << local_time->tm_sec << std::endl;
}

std::string Logger::getTime()
{
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    std::string res = "";
    
    res.append(std::to_string(local_time->tm_hour));
    res.append(":");
    res.append(std::to_string(local_time->tm_min));
    return(res);
}