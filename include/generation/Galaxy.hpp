//
// Created by Iannis on 09/07/2022.
//

#ifndef JEUDELESPACE_GALAXY_HPP
#define JEUDELESPACE_GALAXY_HPP

#include <cstdint>
#include "glm/vec3.hpp"
#include "generation/SolarSystem.hpp"
#include "Utils/LehmerRandom.hpp"

class Galaxy {
private:
    LehmerRandom rand;
public:
    Galaxy(uint32_t parentSeed, int x, int y, int z);
    SolarSystem getSolarSystem(glm::ivec3 position);
    SolarSystem getSolarSystem(int x, int y, int z);
};


#endif //JEUDELESPACE_GALAXY_HPP
