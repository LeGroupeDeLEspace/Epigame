//
// Created by Iannis on 11/07/2022.
//

#include "generation/UniversalPosition.hpp"

UniversalPosition::UniversalPosition(uint32_t seedUniverse, glm::ivec3 galaxy, glm::ivec3 solarSystem) : seedUniverse(seedUniverse), positionGalaxy(galaxy), positionSolarSystem(solarSystem) {}
UniversalPosition::UniversalPosition(uint32_t seedUniverse, glm::ivec3 galaxy) : seedUniverse(seedUniverse), positionGalaxy(galaxy), positionSolarSystem() {}
UniversalPosition::UniversalPosition(uint32_t seedUniverse) : seedUniverse(seedUniverse), positionGalaxy(), positionSolarSystem() {}
UniversalPosition::UniversalPosition() : seedUniverse(), positionGalaxy(), positionSolarSystem() {}

