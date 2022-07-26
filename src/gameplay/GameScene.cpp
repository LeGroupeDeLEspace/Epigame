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
#include <cmath>

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

//    auto ss = SolarSystem(universalPosition);
//    for (int i = 0; i < ss.getNumberOfCelestialBodies(); ++i) {
//        const auto body = registry.create();
//        auto cb = ss.getCelestialBody(i);
//        registry.emplace<LocalPosition>(body, LocalPosition::createLocalPosition(universalPosition,cb.position));
//    }
}

void GameScene::OnDestroy() {
    registry.clear();
}

void GameScene::OnActivate() {
    InputManager::instance().addAction(Input::Event::Move, &onMoveCommand);
}

void GameScene::OnDeactivate() {
    InputManager::instance().removeAction(Input::Event::Move, &onMoveCommand);
}

void GameScene::Update(float deltaTime) {
    if(glm::vec3{0,0,0} != movement) {
        //TODO: change the movement to be fluid.
        universalPosition.positionSolarSystem += movement;
        shouldUpdate = true;
//        glm::i64vec3 mov = glm::i64vec3{movement.x * INT64_MAX, movement.y * INT64_MAX, movement.z * INT64_MAX};
//        auto view = registry.view<LocalPosition>();
//        for(auto [entity, pos]: view.each()) {
//            if(pos.ValidateChange(mov)) {
//                pos.value += mov;
//            } else {
//                registry.destroy(entity);
//            }
//        }
        movement = glm::vec3{0,0,0};
    }
}

void GameScene::LateUpdate(float deltaTime) {
//    if(glm::vec3{0,0,0} != movement) {
//        //TODO: add more celestial bodies
//    }
}

void GameScene::Draw(gr::Graphics& graphics) {
    if(shouldUpdate) {
        graphics.clearBuffer();
        DrawUniverse(graphics);
        shouldUpdate = false;
    }
}

void GameScene::DrawUniverse(gr::Graphics& graphics) const {
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

    if (s.exist) {
        const size_t count = s.getNumberOfCelestialBodies();
        int max = 0;
        for (int i = 0; i < count; ++i) {
            max += (i+1);
        }
        for (int i = 0; i < count; ++i) {
            auto b = s.getCelestialBody(i);
            float s = b.size/50.0f;
            glm::vec3 pos = glm::vec3{
                (float)b.position.position.x/(float)INT_MAX,
                (float)b.position.position.y/(float)INT_MAX,
                (float)b.position.position.z/(float)INT_MAX
            };
            LOG(glm::to_string(pos));
            LOG(std::to_string(s));
            this->DrawPlanet(graphics, pos, glm::vec3(s,s,s), (pos * 0.5f) + 0.5f);
        }
    }
}

void GameScene::DrawPlanet(gr::Graphics& graphics, glm::vec3 center, glm::vec3 size, glm::vec3 color) const {
    glm::vec2 c = glm::vec2 {center.x, center.y};
    glm::vec2 hs = glm::vec2 {size.x * 0.5f, size.y * 0.5f};

    // Vertices of the rectangle
    std::vector<gr::Vertex> vertices = {
            {{c.x-hs.x, c.y-hs.y}, color},
            {{c.x+hs.x, c.y - hs.y}, color},
            {{c.x - hs.x, c.y + hs.y}, color},
            {{c.x + hs.x, c.y + hs.y}, color},
    };

    // Indexes to make a rectangle
    std::vector<uint16_t> index = {
            0, 1, 2, 2, 1, 3,
    };

    gr::Buffer& buffer = graphics.newBuffer(4, 6); // for a rectangle
    buffer.copyData(vertices.data());
    buffer.copyIndexData(index.data());
}

OnMove::OnMove(glm::vec3& movement) : movement(movement) {

}

OnMove::~OnMove() {

}

void OnMove::execute(DataContainer* value) {
    movement = value->getVec3();
}
