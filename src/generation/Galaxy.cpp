//
// Created by Iannis on 09/07/2022.
//

#include "generation/Galaxy.hpp"
#include "Utils/FNV1Hash.hpp"

Galaxy::Galaxy(uint32_t parentSeed, int x, int y, int z) :
        Galaxy(FNV1::Hash(parentSeed, x, y, z)) {

}

Galaxy::Galaxy(uint32_t seed) : rand(seed), name() {
    int len = rand.Next(5, 20);
    for (int i = 0; i < len; ++i) {
        name.push_back('A' + rand.Next(0, 26));
    }
}

std::string Galaxy::getName() const{
    return name;
}

SolarSystem Galaxy::getSolarSystem(glm::ivec3 position) {
    return SolarSystem(rand.initialSeed, position.x, position.y, position.z, name);
}

SolarSystem Galaxy::getSolarSystem(int x, int y, int z) {
    return SolarSystem(rand.initialSeed, x, y, z, name);
}
