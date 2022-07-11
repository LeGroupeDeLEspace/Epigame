//
// Created by Iannis on 04/07/2022.
//

#include "Utils/StringHelper.hpp"

#include <sstream>

std::string StringHelper::pointerToStr(void * p) {
    std::stringstream sstream;
    sstream << p;
    return sstream.str();
}
