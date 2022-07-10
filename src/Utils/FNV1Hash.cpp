//
// Created by Iannis on 09/07/2022.
//

#include "Utils/FNV1Hash.hpp"
const uint32_t fnv_prime = 0x811C9DC5;

uint32_t FNV1::Hash(uint32_t val1, int val2, int val3, int val4){
    uint32_t hash = 0;
    size_t len = 4;
    int v[4] = {
            (int)val1,val2,val3,val4
    };

    for (int i = 0; i < 4; ++i) {
        hash *= fnv_prime;
        hash ^= (v[i]);
    }

    return hash;
}

uint32_t FNV1::Hash(std::string string){
    uint32_t hash = 0;
    size_t len = string.length();

    for (uint32_t i = 0; i < len; i++)
    {
        hash *= fnv_prime;
        hash ^= (string[i]);
    }

    return hash;
}

template<typename T>
uint32_t FNV1::Hash(T array[], size_t length) {
    uint32_t hash = 0;

    for (uint32_t i = 0; i < length; i++)
    {
        hash *= fnv_prime;
        hash ^= (array[i]);
    }
    return hash;
}