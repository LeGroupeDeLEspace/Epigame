//
// Created by Iannis on 10/07/2022.
//

#include "generation/CelestialBody.hpp"


CelestialBody::CelestialBody(std::string name, UniversalPosition position, Coordinates coordinates, float size) : name(
        name), position(position), localPosition(coordinates), size(size) {
}

Coordinates CelestialBody::getlocalPosition() {
    return localPosition;
}
