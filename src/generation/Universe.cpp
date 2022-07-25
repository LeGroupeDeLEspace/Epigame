//
// Created by Iannis on 09/07/2022.
//

#include "generation/Universe.hpp"
#include <system_error>

Universe::Universe() : rand(), position() {

}

Universe::Universe(uint32_t seed) : rand(seed), position(seed) {

}

Universe::Universe(UniversalPosition position) : rand(position.seedUniverse), position(position) {

}

Galaxy Universe::getGalaxy(glm::ivec3 position) {
    return getGalaxy(position.x, position.y, position.z);
}

Galaxy Universe::getGalaxy(int x, int y, int z) {
    return {position, x, y, z};
}

std::vector<CelestialBody> Universe::getCelestialBody(UniversalPosition position, int64_t radius) {
    throw std::runtime_error("get Celestials bodies not implemented yet");
}
