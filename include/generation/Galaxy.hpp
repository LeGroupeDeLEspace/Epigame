//
// Created by Iannis on 09/07/2022.
//

#ifndef JEUDELESPACE_GALAXY_HPP
#define JEUDELESPACE_GALAXY_HPP

#include <cstdint>
#include "glm/vec3.hpp"
#include "generation/SolarSystem.hpp"
#include "utils/LehmerRandom.hpp"

class Galaxy {
private:
    UniversalPosition position;
    LehmerRandom rand;
    std::string name;
public:
    Galaxy(UniversalPosition parentPosition, int x, int y, int z);
    Galaxy(UniversalPosition position);
    std::string getName() const;
    SolarSystem getSolarSystem(glm::ivec3 position);
    SolarSystem getSolarSystem(int x, int y, int z);
};


#endif //JEUDELESPACE_GALAXY_HPP
