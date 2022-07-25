//
// Created by Iannis on 09/07/2022.
//

#ifndef JEUDELESPACE_SOLARSYSTEM_HPP
#define JEUDELESPACE_SOLARSYSTEM_HPP


#include <string>
#include <vector>
#include "generation/CelestialBody.hpp"
#include "generation/Planet.hpp"
#include "utils/LehmerRandom.hpp"

class SolarSystem {
private:
    const UniversalPosition position;
    LehmerRandom rand;
    std::string name;
    size_t numberCelestialBodies;
    std::vector<CelestialBody> celestialBodies;
public:
    const bool exist;
    SolarSystem(UniversalPosition parentPosition, int x, int y, int z);
    SolarSystem(UniversalPosition position);
    std::string getName() const;
    size_t getNumberOfCelestialBodies();
    CelestialBody getCelestialBody(int index);
};


#endif //JEUDELESPACE_SOLARSYSTEM_HPP
