//
// Created by Iannis on 10/07/2022.
//

#ifndef JEUDELESPACE_CELESTIALBODY_HPP
#define JEUDELESPACE_CELESTIALBODY_HPP

#include <string>
#include "glm/vec3.hpp"
class CelestialBody {
public:
    const std::string name;
    const glm::vec3 position;
    CelestialBody(std::string name, glm::vec3 position);
};


#endif //JEUDELESPACE_CELESTIALBODY_HPP
