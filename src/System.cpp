#include "System.hpp"

std::string System::resolvePath(const std::vector<std::string> &parts)
{
    std::string result;
    char separator;
    #ifdef WIN32
        separator = '\\';
    #else
        separator = '/';
    #endif
    // TODO handle absolute paths
    result += std::string(".") + separator;
    for (std::vector<std::string>::const_iterator it = parts.begin(); it != parts.end(); ++it) {
        if (it != parts.begin()) {
            result += separator;
        }
        result += *it;
    }

    return result;
}