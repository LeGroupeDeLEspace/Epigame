//
// Created by Iannis on 10/07/2022.
//

#include "generation/CelestialBody.hpp"


CelestialBody::CelestialBody(std::string name, UniversalPosition position, int size, glm::vec3 color) :
    name(name),
    position(position),
    size(size),
    color(color){
}
