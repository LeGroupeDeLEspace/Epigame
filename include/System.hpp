#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <string>
#include <vector>

class System
{
    public:
        System() = delete;
    
        static std::string resolvePath(const std::vector<std::string> &parts);
};

#endif