#include "Logger.hpp"
#include "ErrorTracking.hpp"
#include "Utils/LehmerRandom.hpp"
#include "generation/Universe.hpp"
#include <iostream>
#include <cassert>

int main()
{
    Logger::log(WARNING, "Here an warning", ERR_LOCATION);
    Universe u=(10);
    auto g = u.getGalaxy(0,0,0);
    for (int x = -50; x < 50; ++x) {
        for (int y = -50; y < 50; ++y) {
            for (int z = -50; z < 50; ++z) {
                auto s = g.getSolarSystem(x,y,z);
                std::cout << s.getName() << "is at {" << x << "," << y << "," << z << "}" << " and it " << (s.exist ? "exist" : "doesn't exist.");
                if (s.exist){
                    std::cout << " " << "It has " << s.getNumberOfCelestialBodies() << " Celestial Bodies.";
                    std::cout << std::endl;
                } else {
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
        }
    }
    // ---
    return 0;
}