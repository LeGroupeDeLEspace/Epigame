//
// Created by Iannis on 05/07/2022.
//

#ifndef JEUDELESPACE_BASERANDOM_HPP
#define JEUDELESPACE_BASERANDOM_HPP

#include <cstdint>

class BaseRandom {
private:
    uint32_t nLehmer;
public:
    BaseRandom();
    BaseRandom(uint32_t seed);

    uint32_t  getSeed();

    uint32_t Next();

};

#endif //JEUDELESPACE_BASERANDOM_HPP
