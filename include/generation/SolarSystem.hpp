//
// Created by Iannis on 09/07/2022.
//

#ifndef JEUDELESPACE_SOLARSYSTEM_HPP
#define JEUDELESPACE_SOLARSYSTEM_HPP


#include <string>
#include <vector>
#include "generation/CelestialBody.hpp"
#include "Utils/LehmerRandom.hpp"

class SolarSystem {
private:
    LehmerRandom rand;
    std::string name;
    std::vector<CelestialBody> celestialBodies;
public:
    const bool exist;
    SolarSystem(uint32_t parentSeed, int x, int y, int z);
    std::string getName() const;
    size_t getNumberOfCelestialBodies();
};


#endif //JEUDELESPACE_SOLARSYSTEM_HPP
