//
// Created by Iannis on 09/07/2022.
//

#include "generation/Universe.hpp"
#include "gameplay/components/LocalPosition.hpp"
#include <system_error>

Universe::Universe() : rand(), position() {

}

Universe::Universe(uint32_t seed) : rand(seed), position(seed) {

}

Universe::Universe(UniversalPosition position) : rand(position.seedUniverse), position(position) {

}

Galaxy Universe::getGalaxy(glm::ivec3 position) {
    return getGalaxy(position.x, position.y, position.z);
}

Galaxy Universe::getGalaxy(int x, int y, int z) {
    return {position, x, y, z};
}

std::vector<CelestialBody> Universe::getCelestialBodies(UniversalPosition position, int64_t radius) {
    std::vector<CelestialBody> vec;
    for (int64_t x = -1; x < 1; ++x) {
        for (int64_t y = -1; y < 1; ++y) {
            for (int64_t z = -1; z < 1; ++z) {
                auto pos = position + UniversalPosition(0, glm::vec3(), glm::vec3(), glm::i64vec3(x*radius, y*radius, z*radius));
                auto s = SolarSystem(pos);
                if (s.exist) {
                    for (int i = 0; i < s.getNumberOfCelestialBodies(); ++i) {
                        auto cb = s.getCelestialBody(i);
                        try {
                            LocalPosition lp = LocalPosition::createLocalPosition(position, cb.position);
                        } catch (std::runtime_error& e) {
                            continue;
                        }
                        vec.emplace_back(cb);
                    }
                }
            }
        }
    }
    return vec;
}
