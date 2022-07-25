//
// Created by Iannis on 25/07/2022.
//

#ifndef JEUDELESPACE_LOCALPOSITION_HPP
#define JEUDELESPACE_LOCALPOSITION_HPP

#include <glm/vec3.hpp>
#include "generation/UniversalPosition.hpp"

struct LocalPosition {
    glm::i64vec3 value;
    bool ValidateChange(glm::i64vec3 change);
    UniversalPosition getGlobalPosition(UniversalPosition position);
    static LocalPosition createLocalPosition(UniversalPosition anchor, UniversalPosition object);
};

#endif //JEUDELESPACE_LOCALPOSITION_HPP
