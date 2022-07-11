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
    size_t numberCelestialBodies;
    std::vector<CelestialBody> celestialBodies;
public:
    const bool exist;
    SolarSystem(uint32_t parentSeed, int x, int y, int z, std::string parentName);
    std::string getName() const;
    size_t getNumberOfCelestialBodies();
    CelestialBody getCelestialBody(int index);
};


#endif //JEUDELESPACE_SOLARSYSTEM_HPP
