#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>

class Logger
{

public:
    Logger(/* args */);
    ~Logger();
    bool writeInFiles(std::string str);
    std::string getDate();
    std::string getTime();

private:
    
};

#endif