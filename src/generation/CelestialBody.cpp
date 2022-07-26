//
// Created by Iannis on 10/07/2022.
//

#include "generation/CelestialBody.hpp"


CelestialBody::CelestialBody(std::string name, UniversalPosition position, int size) : name(
        name), position(position), size(size) {
}

Coordinates CelestialBody::getlocalPosition() {
    Coordinates local = { position.position.x, position.position.y, position.position.z};
    return local;
}
