//
// Created by Iannis on 10/07/2022.
//

#ifndef JEUDELESPACE_SUN_HPP
#define JEUDELESPACE_SUN_HPP

#include "generation/CelestialBody.hpp"

class Sun : CelestialBody {
public:
    Sun(std::string name, glm::vec3 position);
};


#endif //JEUDELESPACE_SUN_HPP
