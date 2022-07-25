//
// Created by Iannis on 25/07/2022.
//

#include <system_error>
#include "gameplay/components/LocalPosition.hpp"

UniversalPosition LocalPosition::getGlobalPosition(UniversalPosition position) {
    UniversalPosition pos = UniversalPosition(position);

    for (int i = 0; i < 3; ++i) {
        if(this->value[i] > 0 && pos.position[i] + this->value[i] <= pos.position[i]) {
            pos.positionSolarSystem[i] ++;
        } else if (this->value[i] < 0 && pos.position[i] + this->value[i] >= pos.position[i]) {
            pos.positionSolarSystem[i] --;
        }
    }

    pos.position += this->value;
    return pos;
}

LocalPosition LocalPosition::createLocalPosition(UniversalPosition anchor, UniversalPosition object) {
    if (anchor.seedUniverse != object.seedUniverse) {
        throw std::runtime_error("The two objects aren't in the same universe.");
    }
    // TODO: handle the case where we are like super close to an other galaxy,
    //  in which case it should be doable to have different universe.
    if (anchor.positionGalaxy != object.positionGalaxy) {
        throw std::runtime_error("The two objects are too far away (more than one galaxy away).");
    }
    glm::ivec3 offsetSS;
    for (int i = 0; i < 3; ++i) {
        if (anchor.positionSolarSystem[i] != object.positionSolarSystem[i]){
            offsetSS[i] += object.positionSolarSystem[i] - anchor.positionSolarSystem[i];
            if(offsetSS[i] > 1 || offsetSS[i] < -1) {
                throw std::runtime_error("The object is too war away (many Solar System away).");
            }
        }
    }

    glm::i64vec3 finalOffset = glm::i64vec3{offsetSS.x * INT64_MAX, offsetSS.y * INT64_MAX, offsetSS.z * INT64_MAX};
    glm::i64vec3 offset = object.position - anchor.position;

    for (int i = 0; i < 3; ++i) {
        if (finalOffset[i] > 0 && offset[i] > 0) {
            throw std::runtime_error("The position is too far away.");
        } else if (finalOffset[i] < 0 && offset[i] < 0) {
            throw std::runtime_error("The position is too far away.");
        }

        finalOffset[i] += offset[i];
    }

    return LocalPosition{finalOffset};
}

bool LocalPosition::ValidateChange(glm::i64vec3 change) {
    for (int i = 0; i < 3; ++i) {
        if ((change[i] > 0 && (value[i] + change[i]) <= value[i]) ||
            (change[i] < 0 && (value[i] + change[i]) >= value[i])) {
            return false;
        }
    }
    return true;
}
