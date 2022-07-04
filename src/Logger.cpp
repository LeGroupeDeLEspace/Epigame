#include "Logger.hpp"
#include "System.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <iomanip>
#include <sstream>

bool Logger::log(MESSAGE type, std::string message, std::string location)
{
    std::fstream fs;
    // create log folder if it doesn't exist
    std::string path = System::resolvePath(std::vector<std::string> {
        "log", getDate().append(".log")
    });

    fs.open(path, std::fstream::out | std::fstream::app);

    fs << getTime() << std::endl;
    fs << getType(type) << ": " << message << std::endl;
    fs << location << std::endl;
    fs << std::endl;

    fs.close();

    std::cout << getTime() << std::endl;
    std::cout << getType(type) << ": " << message << std::endl;
    std::cout << location << std::endl;
    std::cout << std::endl;

    return true;
}

std::string Logger::getDate()
{
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    std::stringstream builder;

    builder << std::put_time(local_time, "%d-%m-%Y");

    return(builder.str());
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

std::string Logger::getType(MESSAGE type)
{
    if (type == VERBOSE)
        return ("VERBOSE");
    else if (type == INFO)
        return ("INFO");
    else if (type == WARNING)
        return("WARNING");
    else if (type == ERROR)
        return("ERROR");
    
    throw std::runtime_error("wrong MESSAGE value");
}