//
// Created by jaro on 11/07/2022.
//

#ifndef JEUDELESPACE_MOON_HPP
#define JEUDELESPACE_MOON_HPP

#include <string>
#include "generation/UniversalPosition.hpp"
#include "CelestialBody.hpp"
#include "utils/LehmerRandom.hpp"

class Moon : public CelestialBody {
public:
    enum type {                   //Based on https://en.wikipedia.org/wiki/List_of_MOON_types#By_composition
        Chthonian,
        Gas_dwarf,
        Gas_giant,
        Desert,
        Ocean,
        Ice,
        Rocky,
        Metal,
        Lava,
        Terran
    };
    type bodyType;
    LehmerRandom rand;
    Moon(std::string name, UniversalPosition position, float size);
};

#endif //JEUDELESPACE_MOON_HPP
