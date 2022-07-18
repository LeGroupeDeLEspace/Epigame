//
// Created by jaro on 11/07/2022.
//

#ifndef JEUDELESPACE_PLANET_HPP
#define JEUDELESPACE_PLANET_HPP

#include <string>
#include "generation/UniversalPosition.hpp"
#include "CelestialBody.hpp"
#include "utils/LehmerRandom.hpp"

class Planet : public CelestialBody {
public:
    enum type {                   //Based on https://en.wikipedia.org/wiki/List_of_planet_types#By_composition
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
    Planet(std::string name, UniversalPosition position, Coordinates localPosition, float size);
};

#endif //JEUDELESPACE_PLANET_HPP
