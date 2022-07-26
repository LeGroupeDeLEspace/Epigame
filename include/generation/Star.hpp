//
// Created by jaro on 11/07/2022.
//

#ifndef JEUDELESPACE_STAR_HPP
#define JEUDELESPACE_STAR_HPP

#include <string>
#include "generation/UniversalPosition.hpp"
#include "CelestialBody.hpp"
#include "utils/LehmerRandom.hpp"

class Star : public CelestialBody {
public:
    enum Type {                   //Based on https://astrobackyard.com/types-of-stars/
        brown_dwarf,
        orange_dwarf,
        red_dwarf,
        white_dwarf,
        yellow_dwarf,
        blue_giant,
        red_giant,
        blue_supergiant,
        red_supergiant,
        black_hole,
        t_tauri,
        neutron,
    };
    Type starType;
    LehmerRandom rand;
    Star(std::string name, UniversalPosition position, float size);
};

#endif //JEUDELESPACE_STAR_HPP
