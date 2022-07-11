//
// Created by Iannis on 05/07/2022.
//

#include <random>
#include "Utils/LehmerRandom.hpp"

LehmerRandom::LehmerRandom() : LehmerRandom(std::random_device()()) {}

LehmerRandom::LehmerRandom(uint32_t seed) : initialSeed(seed) {
    this->nLehmer = seed;
}

uint32_t LehmerRandom::Rand() {
    this->nLehmer += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)this->nLehmer * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;
}

int LehmerRandom::Next() {
    return Next(INT_MIN,INT_MAX);
}

int LehmerRandom::Next(int maxValue) {
    return this->Rand() % maxValue;
}

int LehmerRandom::Next(int minValue, int maxValue) {
    return (this->Rand() % (maxValue - minValue)) + minValue;
}

/// Get a random number between 0 and 1.
/// \return a number between 0 and 1.
float LehmerRandom::NextFloat(){
    return (float)this->Rand() / UINT32_MAX;
}

/// Get a random float between 0 and maxValue.
/// \param maxValue: the upperBounds for the random (include).
/// \return a random float between 0 and maxValue.
float LehmerRandom::NextFloat(float maxValue) {
    return (NextFloat() * maxValue);
}

/// Get a random number between minValue and maxValue.
/// \param minValue: The lower bound of the random (include).
/// \param maxValue The upper bound of the random (include).
/// \return a float between minValue and maxValue.
float LehmerRandom::NextFloat(float minValue, float maxValue) {
    return (NextFloat() * (maxValue - minValue)) + minValue;
}

