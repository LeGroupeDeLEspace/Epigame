//
// Created by Iannis on 05/07/2022.
//

#ifndef JEUDELESPACE_LEHMERRANDOM_HPP
#define JEUDELESPACE_LEHMERRANDOM_HPP

#include <cstdint>

class LehmerRandom {
private:
    uint32_t nLehmer;
    uint32_t Rand();
public:
    const uint32_t initialSeed;

    LehmerRandom();
    LehmerRandom(uint32_t seed);

    int Next();
    int Next(int minValue, int maxValue);

    float NextFloat();
    float NextFloat(float minValue, float maxValue);

};

#endif //JEUDELESPACE_LEHMERRANDOM_HPP
