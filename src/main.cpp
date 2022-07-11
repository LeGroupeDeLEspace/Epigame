#include "Logger.hpp"
#include "ErrorTracking.hpp"
#include "generation/Universe.hpp"
#include <iostream>

int main()
{
    Logger::log(WARNING, "Here a warning", ERR_LOCATION);
    Universe u=(10);
    auto g = u.getGalaxy(0,0,0);
    for (int x = -10; x < 10; ++x) {
        for (int y = -10; y < 10; ++y) {
            for (int z = -10; z < 10; ++z) {
                auto s = g.getSolarSystem(x,y,z);
                std::cout << s.getName() << "is at {" << x << "," << y << "," << z << "}" << " in the " << g.getName() << " galaxy and it " << (s.exist ? "exists" : "doesn't exist.");
                if (s.exist){
                    std::cout << " " << "It has " << s.getNumberOfCelestialBodies() << " Celestial Bodies.";
                    std::cout << std::endl;
                    for (int i = 0; i < s.getNumberOfCelestialBodies(); ++i) {
                        auto b = s.getCelestialBody(i);
                        std::cout << '\t' << b.name << std::endl;
                    }
                } else {
                    std::cout << std::endl;
                }
                std::cout<< "------------------------" << std::endl;
            }
        }
    }
    // ---
    return 0;
}