//
// Created by Iannis on 10/07/2022.
//

#ifndef JEUDELESPACE_CELESTIALBODY_HPP
#define JEUDELESPACE_CELESTIALBODY_HPP

#include <string>
#include "generation/UniversalPosition.hpp"
class CelestialBody {
public:
    const std::string name;
    const UniversalPosition position;
    const float size;
    CelestialBody(std::string name, UniversalPosition position, float size);
};


#endif //JEUDELESPACE_CELESTIALBODY_HPP
