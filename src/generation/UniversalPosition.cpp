//
// Created by Iannis on 11/07/2022.
//

#include "generation/UniversalPosition.hpp"

UniversalPosition::UniversalPosition() : position() {

}

UniversalPosition::UniversalPosition(float position[9]) : position() {
    for (int i = 0; i < 9; ++i) {
        this->position[i] = position[i];
    }
}

UniversalPosition::UniversalPosition(glm::vec3 universe, glm::vec3 galaxy, glm::vec3 solarSystem) : position() {
    this->position[0] = universe[0];
    this->position[1] = universe[1];
    this->position[2] = universe[2];

    this->position[3] = galaxy[0];
    this->position[4] = galaxy[1];
    this->position[5] = galaxy[2];

    this->position[6] = solarSystem[0];
    this->position[7] = solarSystem[1];
    this->position[8] = solarSystem[2];
}

glm::vec3 UniversalPosition::getPositionUniverse() {
    return glm::vec3(this->position[0], this->position[1], this->position[2]);
}


glm::vec3 UniversalPosition::getPositionInGalaxy() {
    return glm::vec3(this->position[3], this->position[4], this->position[5]);
}

glm::vec3 UniversalPosition::getPositionSolarSystem() {
    return glm::vec3(this->position[6], this->position[7], this->position[8]);
}
