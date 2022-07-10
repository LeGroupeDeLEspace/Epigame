//
// Created by Iannis on 09/07/2022.
//

#include "generation/Galaxy.hpp"
#include "Utils/FNV1Hash.hpp"

Galaxy::Galaxy(uint32_t parentSeed, int x, int y, int z) :
    rand(FNV1::Hash(parentSeed,x,y,z))
{

}

SolarSystem Galaxy::getSolarSystem(glm::ivec3 position) {
    return SolarSystem(rand.initialSeed,position.x,position.y,position.z);
}

SolarSystem Galaxy::getSolarSystem(int x, int y, int z) {
    return SolarSystem(rand.initialSeed,x,y,z);
}
