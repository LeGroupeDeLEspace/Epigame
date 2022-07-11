//
// Created by Iannis on 11/07/2022.
//

#ifndef JEUDELESPACE_UNIVERSALPOSITION_HPP
#define JEUDELESPACE_UNIVERSALPOSITION_HPP

#include "glm/vec3.hpp"

class UniversalPosition {
private:
    glm::vec3 positionUniverse;
    glm::vec3 positionGalaxy;
    glm::vec3 positionSolarSystem;
public:
    UniversalPosition();
    UniversalPosition(float position[9]);
    UniversalPosition(glm::vec3 universe, glm::vec3 galaxy, glm::vec3 solarSystem);
    glm::vec3 getPositionUniverse();
    glm::vec3 getPositionInGalaxy();
    glm::vec3 getPositionSolarSystem();
};


#endif //JEUDELESPACE_UNIVERSALPOSITION_HPP
