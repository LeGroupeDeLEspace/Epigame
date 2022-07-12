//
// Created by Iannis on 10/07/2022.
//

#ifndef JEUDELESPACE_CELESTIALBODY_HPP
#define JEUDELESPACE_CELESTIALBODY_HPP

#include <string>
#include "generation/UniversalPosition.hpp"
class CelestialBody {
private:
    const float distanceFromStar;
public:
    const std::string name;
    const UniversalPosition position;
    const float size;
    CelestialBody(std::string name, UniversalPosition position, float size);
    float getDistanceFromStar(){return distanceFromStar;}
};


#endif //JEUDELESPACE_CELESTIALBODY_HPP
