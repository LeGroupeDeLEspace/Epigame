//
// Created by Iannis on 05/07/2022.
//

#ifndef JEUDELESPACE_BASERANDOM_HPP
#define JEUDELESPACE_BASERANDOM_HPP

#include <cstdint>

class BaseRandom {
private:
    uint32_t nLehmer;
    uint32_t Rand();
public:
    const uint32_t initialSeed;

    BaseRandom();
    BaseRandom(uint32_t seed);

    int Next();
    int Next(int minValue, int maxValue);

    float NextFloat();
    float NextFloat(float minValue, float maxValue);

};

#endif //JEUDELESPACE_BASERANDOM_HPP
