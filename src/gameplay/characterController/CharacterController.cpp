//
// Created by ianpo on 16/07/2022.
//

#include "gameplay/characterController/CharacterController.hpp"

void CharacterController::enable() {
    status = true;
}
void CharacterController::update() {

}

void CharacterController::disable() {
    status = false;
}

bool CharacterController::isEnable() {
    return status;
}
