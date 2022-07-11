//
// Created by Iannis on 09/07/2022.
//

#include "generation/Universe.hpp"

Universe::Universe() : rand() {

}

Universe::Universe(uint32_t seed) : rand(seed) {

}

Galaxy Universe::getGalaxy(glm::ivec3 position) {
    return getGalaxy(position.x, position.y, position.z);
}

Galaxy Universe::getGalaxy(int x, int y, int z) {
    return {rand.initialSeed,x,y,z};
}
