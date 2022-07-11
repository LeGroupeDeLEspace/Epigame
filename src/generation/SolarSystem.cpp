//
// Created by Iannis on 09/07/2022.
//

#include <system_error>
#include "generation/SolarSystem.hpp"
#include "Utils/FNV1Hash.hpp"

SolarSystem::SolarSystem(uint32_t parentSeed, int x, int y, int z) :
        rand(FNV1::Hash(parentSeed,x,y,z)),
        name(),
        exist(rand.Next(255)>25),
        numberCelestialBodies(rand.Next(5,25)),
        celestialBodies()
{
    int len = rand.Next(5,20);
    for (int i = 0; i < len; ++i) {
        name.push_back('A' + rand.Next(0, 26));
    }
    if (!exist) return;

    // Reserve the place for the number of CelestialBodies I will need to not re-allocate at every emplace_back.
//    celestialBodies.reserve(numberCelestialBodies);

    // TODO: create the sun at 0.
    celestialBodies.emplace_back(std::string(name).append("_SUN"), UniversalPosition(glm::vec3(), glm::vec3(), glm::vec3(x,y,z)), rand.Next(25,50));
    for (int i = 1; i < numberCelestialBodies; ++i) {
        // TODO: Create all the Planet
        celestialBodies.emplace_back(std::string(name).append("_PLANET_").append(std::to_string(i)), UniversalPosition(glm::vec3(), glm::vec3(), glm::vec3(x,y,z)), rand.Next(5,20));
    }

}

std::string SolarSystem::getName() const{
    return name;
}

size_t SolarSystem::getNumberOfCelestialBodies() {
    return this->exist ? this->numberCelestialBodies : 0;
}

CelestialBody SolarSystem::getCelestialBody(int index) {
    if (index < 0 || index >= this->numberCelestialBodies) {
        throw std::runtime_error(std::string("The index ").append(std::to_string(index).append(" is invalid.")));
    }
    return celestialBodies[index];
}
