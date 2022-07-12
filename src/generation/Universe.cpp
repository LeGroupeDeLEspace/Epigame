//
// Created by Iannis on 09/07/2022.
//

#include "generation/Universe.hpp"

Universe::Universe() : rand(), position() {

}

Universe::Universe(uint32_t seed) : rand(seed), position(seed) {

}

Universe::Universe(UniversalPosition position) : rand(position.getSeedUniverse()), position(position) {

}

Galaxy Universe::getGalaxy(glm::ivec3 position) {
    return getGalaxy(position.x, position.y, position.z);
}

Galaxy Universe::getGalaxy(int x, int y, int z) {
    return {position, x, y, z};
}
