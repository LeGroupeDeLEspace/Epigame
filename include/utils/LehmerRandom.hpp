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
    int Next(int maxValue);
    int Next(int minValue, int maxValue);

    int64_t NextLong();
    int64_t NextLong(int64_t maxValue);
    int64_t NextLong(int64_t minValue, int64_t maxValue);

    float NextFloat();
    float NextFloat(float maxValue);
    float NextFloat(float minValue, float maxValue);

    double NextDouble();
    double NextDouble(double maxValue);
    double NextDouble(double minValue, double maxValue);

    bool NextBool();
};

#endif //JEUDELESPACE_LEHMERRANDOM_HPP
