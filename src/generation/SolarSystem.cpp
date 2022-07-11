//
// Created by Iannis on 09/07/2022.
//

#include "generation/SolarSystem.hpp"
#include "generation/Sun.hpp"
#include "generation/Planet.hpp"
#include "Utils/FNV1Hash.hpp"

SolarSystem::SolarSystem(uint32_t parentSeed, int x, int y, int z) :
        rand(FNV1::Hash(parentSeed,x,y,z)),
        name(),
        exist(rand.Next(255)>25),
        celestialBodies(rand.Next(5,25), CelestialBody("no_name",UniversalPosition(), 0))
{
    int len = rand.Next(5,20);
    for (int i = 0; i < len; ++i) {
        name.push_back('A' + rand.Next(0, 26));
    }
    if (!exist) return;

    // TODO: create the sun at 0.
    for (int i = 1; i < celestialBodies.size(); ++i) {
        // TODO: Create all the Planet
    }

}

std::string SolarSystem::getName() const{
    return name;
}

size_t SolarSystem::getNumberOfCelestialBodies() {
    return this->celestialBodies.size();
}
