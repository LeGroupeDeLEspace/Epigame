//
// Created by Iannis on 11/07/2022.
//

#include "generation/UniversalPosition.hpp"

UniversalPosition::UniversalPosition(uint32_t seedUniverse, glm::ivec3 galaxy, glm::ivec3 solarSystem, glm::i64vec3 position) : seedUniverse(seedUniverse), positionGalaxy(galaxy), positionSolarSystem(solarSystem), position(position) {}
UniversalPosition::UniversalPosition(uint32_t seedUniverse, glm::ivec3 galaxy, glm::ivec3 solarSystem) : seedUniverse(seedUniverse), positionGalaxy(galaxy), positionSolarSystem(solarSystem) {}
UniversalPosition::UniversalPosition(uint32_t seedUniverse, glm::ivec3 galaxy) : seedUniverse(seedUniverse), positionGalaxy(galaxy) {}
UniversalPosition::UniversalPosition(uint32_t seedUniverse) : seedUniverse(seedUniverse) {}

bool operator==(const UniversalPosition &lhs, const UniversalPosition &rhs) {
    return lhs.seedUniverse == rhs.seedUniverse &&
    lhs.positionGalaxy == rhs.positionGalaxy &&
    lhs.positionSolarSystem == rhs.positionSolarSystem;
}

bool operator!=(const UniversalPosition &lhs, const UniversalPosition &rhs) {
    return lhs.seedUniverse != rhs.seedUniverse ||
    lhs.positionGalaxy != rhs.positionGalaxy ||
    lhs.positionSolarSystem != rhs.positionSolarSystem;
}

UniversalPosition operator+(const UniversalPosition& lhs, const UniversalPosition& rhs){
    UniversalPosition res = lhs;

    for (int i = 0; i < 3; ++i) {
        res.position[i] += rhs.position[i];
        if(rhs.position[i] > 0 && res.position[i] < lhs.position[i]) {
            res.positionSolarSystem[i] ++;
        } else if (rhs.position[i] < 0 && res.position[i] > lhs.position[i]) {
            res.positionSolarSystem[i] --;
        }
    }

    for (int i = 0; i < 3; ++i) {
        res.positionSolarSystem[i] += rhs.positionSolarSystem[i];
        if(rhs.positionSolarSystem[i] > 0 && res.positionSolarSystem[i] < lhs.positionSolarSystem[i]) {
            res.positionGalaxy[i] ++;
        } else if (rhs.positionSolarSystem[i] < 0 && res.positionSolarSystem[i] > lhs.positionSolarSystem[i]) {
            res.positionGalaxy[i] --;
        }
    }

    res.positionGalaxy += rhs.positionGalaxy;
    return res;
}

UniversalPosition operator-(const UniversalPosition& lhs, const UniversalPosition& rhs){
    UniversalPosition res = lhs;
    res.position = -res.position;
    res.positionSolarSystem = -res.positionSolarSystem;
    res.positionGalaxy = -res.positionGalaxy;
    return res + rhs;
}

UniversalPosition& UniversalPosition::operator+=(const UniversalPosition &rhs) {
    *this = *this + rhs;
    return *this;
}

UniversalPosition& UniversalPosition::operator-=(const UniversalPosition &rhs) {
    *this = *this - rhs;
    return *this;
}