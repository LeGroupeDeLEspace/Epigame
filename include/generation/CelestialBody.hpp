//
// Created by Iannis on 10/07/2022.
//

#ifndef JEUDELESPACE_CELESTIALBODY_HPP
#define JEUDELESPACE_CELESTIALBODY_HPP

#include <string>
#include "generation/UniversalPosition.hpp"
#include "LocalCoordinates.hpp"

class CelestialBody {
public:
    const std::string name;
    const UniversalPosition position;
    const int size;
    enum Colour {
        /*Stars colours from 0 to 6*/
        star_blue,
        star_white,
        star_yellow,
        star_orange,
        star_red,
        star_brown,
        black_hole,
        /*Planets colours from 7 to 16*/
        planet_blue, //for gas, ocean, icy or terran planets
        planet_orange, //for chtonian, gas, rocky, and lava planets
        planet_red, //for gas, desert, rocky, and lava
        planet_brown, //for gas, desert and rocky planets
        green, //for gas, ocean and terran planets
        purple, //for gas, ocean and terran planets
        gray, //for desert and rocky planets
        ash, //for desert, terran and rocky plannets
        teal, //for ocean, ice and rocky planets
        metal //for metal planets
    };
    Colour color;

    CelestialBody(std::string name, UniversalPosition position, int size);

    Coordinates getlocalPosition();
};


#endif //JEUDELESPACE_CELESTIALBODY_HPP
