#include "System.hpp"
#include <fstream>
#include <filesystem>


namespace su {

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

std::vector<char> System::readFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filename);
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}

    bool System::createFolder(const std::filesystem::path &path) {
        if(!std::filesystem::exists(path)) {
            return false;
        }

        if (std::filesystem::is_directory(path)){
            return true;
        }

        return std::filesystem::create_directories(path);
    }

}