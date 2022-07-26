//
// Created by Iannis on 09/07/2022.
//

#include <system_error>
#include "generation/SolarSystem.hpp"
#include "generation/Galaxy.hpp"
#include "utils/FNV1Hash.hpp"

SolarSystem::SolarSystem(UniversalPosition parentPosition, int x, int y, int z) :
        SolarSystem(UniversalPosition(parentPosition.seedUniverse,parentPosition.positionGalaxy,glm::ivec3(x,y,z))){

}

SolarSystem::SolarSystem(UniversalPosition position) :
        position(position),
        rand(FNV1::Hash( // Generating the SolarSystem seed
                FNV1::Hash( // Regenerating the parent Seed
                        position.seedUniverse,
                        position.positionGalaxy.x,
                        position.positionGalaxy.y,
                        position.positionGalaxy.z),
                position.positionSolarSystem.x,
                position.positionSolarSystem.y,
                position.positionSolarSystem.z)),
        name(),
        exist(rand.Next(255) > 25),
        numberCelestialBodies(rand.Next(5, 25)),
        celestialBodies()
{
        int len = rand.Next(5, 20);
        name.append(Galaxy(position).getName() + "-");
        for (int i = 0; i < len; ++i) {
            name.push_back('A' + rand.Next(0, 26));
        }
    if (!exist) return;

    // Reserve the place for the number of CelestialBodies I will need to not re-allocate at every emplace_back.
    celestialBodies.reserve(numberCelestialBodies);

    // TODO: create the sun at 0.
    auto sunPos = UniversalPosition(position);
    sunPos.position = glm::i64vec3{0, 0, 0};
    celestialBodies.emplace_back(std::string(name).append("-SUN"),
                                 sunPos,
                                 rand.Next(25, 50));
    for (int i = 1; i < numberCelestialBodies; ++i) {
        // TODO: Create all the Planet
        auto pos = UniversalPosition(position);
        pos.position = glm::i64vec3(rand.Next(),rand.Next(),rand.Next());
        celestialBodies.emplace_back(std::string(name).append("-PLANET-").append(std::to_string(i)),
                                     pos,
                                     rand.Next(5, 20));
    }

}

std::string SolarSystem::getName() const {
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