//
// Created by Iannis on 19/07/2022.
//

#include "gameplay/GameScene.hpp"
#include "utils/DataContainer.hpp"
#include "inputs/InputManager.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "gameplay/components/Rotation.hpp"
#include "generation/UniversalPosition.hpp"
#include "gameplay/components/LocalPosition.hpp"

#define LOG(s) std::cout << s << std::endl
#define LOGENDL() std::cout << std::endl

// Avec la universalPosition, on a la position de la camera dans l'espace. Et les autres objects ne sont que des offsets de cette position
// La rotation global corresponds a la direction dans laquelle regarde le joueur (quaternion * {0,0,1})
// Tout les objets ont donc un i64vec3 pour leurs position,
// un quaternion pour leurs rotation
// et suivant les objets une struct type planet / sun / ... qui les aideront a définir ce qu'ils font et ne font pas
// Ou juste un celestial body avec plus de paramètres... plus logique aussi.

GameScene::GameScene() :
        onMoveCommand(this->movement),
        shouldUpdate(false) {}

void GameScene::OnCreate() {
    player = registry.create();
    registry.emplace<UniversalPosition>(player);
    registry.emplace<Rotation>(player);

    auto ss = SolarSystem(universalPosition);
    for (int i = 0; i < ss.getNumberOfCelestialBodies(); ++i) {
        const auto body = registry.create();
        registry.emplace<LocalPosition>(body, LocalPosition::createLocalPosition(universalPosition,ss.getCelestialBody(i).position));
    }
}

void GameScene::OnDestroy() {
    registry.clear();
}

void GameScene::OnActivate() {
    InputManager::instance().addAction(Input::Event::Move, &onMoveCommand);
    DrawUniverse();
}

void GameScene::OnDeactivate() {
    InputManager::instance().removeAction(Input::Event::Move, &onMoveCommand);
}

void GameScene::Update(float deltaTime) {
    if(glm::vec3{0,0,0} != movement) {
        //TODO: change the movement to be fluid.
        universalPosition.positionSolarSystem += movement;
        shouldUpdate = true;
    }
}

void GameScene::LateUpdate(float deltaTime) {

}

void GameScene::Draw(GLFWwindow &window) {
    if(shouldUpdate) {
        DrawUniverse();
        shouldUpdate = false;
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

OnMove::OnMove(glm::vec3& movement) : movement(movement) {

}

OnMove::~OnMove() {

}

void OnMove::execute(DataContainer* value) {
    movement = value->getVec3();
}
