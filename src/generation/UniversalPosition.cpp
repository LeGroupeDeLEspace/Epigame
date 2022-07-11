//
// Created by Iannis on 11/07/2022.
//

#include "generation/UniversalPosition.hpp"

UniversalPosition::UniversalPosition() : positionUniverse(), positionGalaxy(), positionSolarSystem() {

}

UniversalPosition::UniversalPosition(glm::vec3 universe, glm::vec3 galaxy, glm::vec3 solarSystem) : positionUniverse(universe), positionGalaxy(galaxy), positionSolarSystem(solarSystem) {

}

glm::vec3 UniversalPosition::getPositionUniverse() {
    return positionUniverse;
}


glm::vec3 UniversalPosition::getPositionInGalaxy() {
    return positionGalaxy;
}

glm::vec3 UniversalPosition::getPositionSolarSystem() {
    return positionSolarSystem;
}
