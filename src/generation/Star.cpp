//
// Created by mgkan on 18/07/2022.
//

#include "generation/Star.hpp"
#include "utils/FNV1Hash.hpp"


Star::Star(std::string name, UniversalPosition position, Coordinates localPosition, float size) : CelestialBody(name, position, localPosition, size), rand(FNV1::Hash( // Generating the SolarSystem seed
        FNV1::Hash( // Regenerating the parent Seed
                position.seedUniverse,
                position.positionGalaxy.x,
                position.positionGalaxy.y,
                position.positionGalaxy.z),
        position.positionSolarSystem.x,
        position.positionSolarSystem.y,
        position.positionSolarSystem.z)) {
    bodyType = type(rand.Next(0, 9));
}