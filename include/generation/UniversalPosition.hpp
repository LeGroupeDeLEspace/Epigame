//
// Created by Iannis on 11/07/2022.
//

#ifndef JEUDELESPACE_UNIVERSALPOSITION_HPP
#define JEUDELESPACE_UNIVERSALPOSITION_HPP

#include "glm/vec3.hpp"

class UniversalPosition {
private:
    uint32_t seedUniverse;
    glm::vec3 positionGalaxy;
    glm::vec3 positionSolarSystem;
public:
    UniversalPosition(uint32_t seedUniverse, glm::vec3 galaxy, glm::vec3 solarSystem);
    UniversalPosition(uint32_t seedUniverse, glm::vec3 galaxy);
    UniversalPosition(uint32_t seedUniverse);
    UniversalPosition();
    uint32_t getSeedUniverse();
    glm::vec3 getPositionGalaxy();
    glm::vec3 getPositionSolarSystem();
};


#endif //JEUDELESPACE_UNIVERSALPOSITION_HPP
