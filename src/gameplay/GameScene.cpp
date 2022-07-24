//
// Created by Iannis on 19/07/2022.
//

#include "gameplay/GameScene.hpp"
#include "utils/DataContainer.hpp"
#include "inputs/InputManager.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#define LOG(s) std::cout << s << std::endl
#define LOGENDL() std::cout << std::endl

OnMove::OnMove(UniversalPosition& universalPosition) : universalPosition(universalPosition) {

}

OnMove::~OnMove() {

}

void OnMove::execute(DataContainer* value) {
    universalPosition.positionSolarSystem += value->getVec3();
}


GameScene::GameScene() : previousUniversalPosition(), universalPosition(previousUniversalPosition), onMoveCommand(this->universalPosition) {

}

GameScene::GameScene(UniversalPosition& universalPosition): previousUniversalPosition(universalPosition), universalPosition(universalPosition), onMoveCommand(this->universalPosition) {

}

void GameScene::OnCreate() {

}

void GameScene::OnDestroy() {

}

void GameScene::OnActivate() {
    InputManager::instance().addAction(Input::Event::Move, &onMoveCommand);
    DrawUniverse();
}

void GameScene::OnDeactivate() {
    InputManager::instance().removeAction(Input::Event::Move, &onMoveCommand);
}

void GameScene::Draw(GLFWwindow &window) {
    if(previousUniversalPosition != universalPosition) {
        DrawUniverse();
        previousUniversalPosition = universalPosition;
    }
}

void GameScene::DrawUniverse() const {
    auto u = Universe(universalPosition.seedUniverse);
    auto g = u.getGalaxy(universalPosition.positionGalaxy);
    auto s = g.getSolarSystem(universalPosition.positionSolarSystem);

    LOG("We are in the Universe of seed " << std::to_string(universalPosition.seedUniverse));
    LOG("We are in the Galaxy " << g.getName() << " at position "
                                << glm::to_string(universalPosition.positionGalaxy));
    LOG("We are in the Solar System " << s.getName() << " at position "
                                      << glm::to_string(universalPosition.positionSolarSystem));
    if (s.exist) {
        LOG(s.getName() << " has " << std::to_string(s.getNumberOfCelestialBodies()) << " Celestial Bodies");
    } else {
        LOG(s.getName() << " isn't really a Solar System. It doesn't even have a sun...");
    }
    LOG("==================================================");
    LOGENDL();
}
