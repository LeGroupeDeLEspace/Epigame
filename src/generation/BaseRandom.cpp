//
// Created by Iannis on 05/07/2022.
//

#include <random>
#include "generation/BaseRandom.hpp"

BaseRandom::BaseRandom() : BaseRandom(std::random_device()()) {}

BaseRandom::BaseRandom(uint32_t seed) {
    this->nLehmer = seed;
}

uint32_t BaseRandom::getSeed() {
    return this->nLehmer;
}

uint32_t BaseRandom::Next() {
    this->nLehmer += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)this->nLehmer * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;
}
