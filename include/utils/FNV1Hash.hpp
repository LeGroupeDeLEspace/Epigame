//
// Created by Iannis on 09/07/2022.
//

#ifndef JEUDELESPACE_FNV1HASH_HPP
#define JEUDELESPACE_FNV1HASH_HPP

#include <string>
#include <cstdint>

namespace FNV1 {
    uint32_t Hash(std::string string);
    uint32_t Hash(uint32_t val1, int val2, int val3, int val4);
    template<typename T> uint32_t Hash(T array[], size_t length);
}

#endif //JEUDELESPACE_FNV1HASH_HPP
