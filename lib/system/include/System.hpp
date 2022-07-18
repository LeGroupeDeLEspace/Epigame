#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <string>
#include <vector>
#include <filesystem>

namespace su {

    class System
    {
        public:
            System() = delete;
        
            static std::string resolvePath(const std::vector<std::string> &parts);
            static std::vector<char> readFile(const std::string& filename);
            static bool createFolder(const std::filesystem::path &path);
    };

}

#endif