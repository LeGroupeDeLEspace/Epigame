//
// Created by Iannis on 09/07/2022.
//

#ifndef JEUDELESPACE_UNIVERSE_HPP
#define JEUDELESPACE_UNIVERSE_HPP

#include "glm/vec3.hpp"
#include "utils/LehmerRandom.hpp"
#include "generation/Galaxy.hpp"

class Universe {
private:
LehmerRandom rand;
public:
    Universe();
    Universe(uint32_t seed);
    Galaxy getGalaxy(glm::ivec3 position);
    Galaxy getGalaxy(int x, int y, int z);
};


#endif //JEUDELESPACE_UNIVERSE_HPP
