//
// Created by mgkan on 18/07/2022.
//

#include "generation/Star.hpp"
#include "utils/FNV1Hash.hpp"


Star::Star(std::string name, UniversalPosition position, float size) : CelestialBody(name, position, size), rand(FNV1::Hash( // Generating the SolarSystem seed
        FNV1::Hash( // Regenerating the parent Seed
                position.seedUniverse,
                position.positionGalaxy.x,
                position.positionGalaxy.y,
                position.positionGalaxy.z),
        position.positionSolarSystem.x,
        position.positionSolarSystem.y,
        position.positionSolarSystem.z)) {
    starType = Type(rand.Next(0, 11));
    switch (starType) {

        case brown_dwarf:
            color = Colour(5);
            break;
        case orange_dwarf:
            color = Colour(3);
            break;
        case red_dwarf:
            color = Colour(4);
            break;
        case white_dwarf:
            color = Colour(1);
            break;
        case yellow_dwarf:
            color = Colour(2);
            break;
        case blue_giant:
            color = Colour(0);
            break;
        case red_giant:
            color = Colour(4);
            break;
        case blue_supergiant:
            color = Colour(0);
            break;
        case red_supergiant:
            color = Colour(4);
            break;
        case black_hole:
            color = Colour(6);
            break;
        case t_tauri:
            color = Colour(2);
            break;
        case neutron:
            color = Colour(rand.Next(0, 1));
            break;
    }
}