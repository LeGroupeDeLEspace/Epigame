#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>

enum MESSAGE {VERBOSE, INFO, WARNING, ERROR};

class Logger
{

public:
    Logger(/* args */);
    ~Logger();
    bool log(MESSAGE type, std::string message, std::string location);
    std::string getDate();
    std::string getTime();
    std::string getType(MESSAGE type);

private:
    
};

#endif