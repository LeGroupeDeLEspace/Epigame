#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>

enum MESSAGE {VERBOSE, INFO, WARNING, ERROR};

class Logger
{

public:
    Logger() = delete;
    static bool log(MESSAGE type, std::string message, std::string location);

private:
    static std::string getDate();
    static std::string getTime();
    static std::string getType(MESSAGE type);
    
};

#endif