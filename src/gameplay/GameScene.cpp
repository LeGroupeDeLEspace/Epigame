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
#include "gameplay/components/Color.hpp"
#include "gameplay/components/Size.hpp"
#include "Shapes/CircleShape.hpp"
#include <cmath>

#define LOG(s) std::cout << s << std::endl
#define LOGENDL() std::cout << std::endl

#define SPEED_MOVE (INT64_MAX/100)
//#define SPEED_MOVE (INT64_MAX)

#define VIEW_DISTANCE ((INT64_MAX/10)*8)

// Avec la universalPosition, on a la position de la camera dans l'espace. Et les autres objects ne sont que des offsets de cette position
// La rotation global corresponds a la direction dans laquelle regarde le joueur (quaternion * {0,0,1})
// Tout les objets ont donc un i64vec3 pour leurs position,
// un quaternion pour leurs rotation
// et suivant les objets une struct type planet / sun / ... qui les aideront a définir ce qu'ils font et ne font pas
// Ou juste un celestial body avec plus de paramètres... plus logique aussi.

GameScene::GameScene() :
        universalPosition(50, glm::ivec3(), glm::ivec3(), glm::i64vec3()),
        onMoveCommand(this->movement),
        shouldUpdate(false) {}

void GameScene::OnCreate() {
    player = registry.create();
    registry.emplace<UniversalPosition>(player);
    registry.emplace<Rotation>(player, glm::dquat{0,0,0,1});

//    auto ss = SolarSystem(universalPosition);
//    auto bodies = Universe::getCelestialBodies(universalPosition, VIEW_DISTANCE);
//    for (auto& cb: bodies) {
//        try {
//            const auto body = registry.create();
//            registry.emplace<LocalPosition>(body, lp);
//            registry.emplace<Size>(body, cb.size);
//            glm::vec3 c = glm::vec3 {
//                    (long double)cb.position.position.x /(long double)INT_MAX,
//                    (long double)cb.position.position.y /(long double)INT_MAX,
//                    (long double)cb.position.position.z /(long double)INT_MAX,
//            };
//
//            c *= 0.5f;
//            c += 0.5f;
//            registry.emplace<Color>(body, c);
//        } catch (std::runtime_error& e) {
//            continue;
//        }
//    }
//    shouldUpdate = true;
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
        shouldUpdate = true;
        glm::i64vec3 mov = glm::i64vec3{(int64_t)movement.x * SPEED_MOVE, (int64_t)movement.y * SPEED_MOVE, (int64_t)movement.z * SPEED_MOVE};
        auto fullMov = UniversalPosition(0,glm::ivec3(),glm::ivec3(),mov);
        auto newPos = this->universalPosition + fullMov;
//        auto view = registry.view<UniversalPosition, Size>();
//        for(auto [entity, pos, size]: view.each()) {
//            auto distance = pos - newPos;
//            if(distance.positionGalaxy != glm::ivec3() && distance.positionSolarSystem != glm::ivec3()) {
//                registry.destroy(entity);
//            }
//        }
        universalPosition = newPos;
        registry.replace<UniversalPosition>(player, this->universalPosition);
    }
}

void GameScene::LateUpdate(float deltaTime) {
//    if(glm::vec3{0,0,0} != movement) {
//        auto view = registry.view<LocalPosition>();
//        auto bodies = Universe::getCelestialBodies(universalPosition, VIEW_DISTANCE);
//        for (auto& cb: bodies) {
//            bool stop = false;
//            for (auto [entity, pos]: view.each()) {
//                if(cb.position == pos.getGlobalPosition(universalPosition)) {
//                    stop = true;
//                    break;
//                }
//            }
//            if(stop) continue;
//
//            try {
//                LocalPosition lp = LocalPosition::createLocalPosition(universalPosition,cb.position);
//                const auto body = registry.create();
//                registry.emplace<LocalPosition>(body, lp);
//                registry.emplace<Size>(body, cb.size);
//                glm::dvec3 c = glm::dvec3 {
//                        (long double)cb.position.position.x /(long double)INT_MAX,
//                        (long double)cb.position.position.y /(long double)INT_MAX,
//                        (long double)cb.position.position.z /(long double)INT_MAX,
//                };
//
//                c *= 0.5f;
//                c += 0.5f;
//                registry.emplace<Color>(body, c);
//                LOGENDL();
//            } catch (std::runtime_error& e) {
//                continue;
//            }
//        }
//        movement = glm::vec3();
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

//    auto view = registry.view<LocalPosition, Size, Color>();
    auto playerPos = registry.get<UniversalPosition>(this->player);
    auto celestialBodies = Universe::getCelestialBodies(playerPos, VIEW_DISTANCE);

    auto direction = glm::dvec3{0,0,1};
    auto rotation = registry.get<Rotation>(player).value;

    // Multiply Quaternion by vector
    auto xyz = glm::dvec3{rotation.x,rotation.y,rotation.z};
    auto t = 2.0 * glm::cross(xyz, direction);
    direction = direction +  rotation.w * t + glm::cross(xyz, t);
    // End of Multiplication

    int num = 0;
//    for (auto [entity, pos, size, color]: view.each()) {
    for (auto celestialBody: celestialBodies) {
        auto size = celestialBody.size;
        auto pos = LocalPosition::createLocalPosition(playerPos, celestialBody.position);
        glm::dvec3 p = glm::dvec3{
                (long double)pos.value.x/(long double)VIEW_DISTANCE,
                (long double)pos.value.y/(long double)VIEW_DISTANCE,
                (long double)pos.value.z/(long double)VIEW_DISTANCE
        };

        float s = size / 50.0;
        if(glm::dot(glm::normalize(direction), glm::normalize(p)) > 0) {
            auto color = glm::vec3 {
                std::abs((float)celestialBody.position.position.x) / (float)INT64_MAX,
                std::abs((float)celestialBody.position.position.y) / (float)INT64_MAX,
                std::abs((float)celestialBody.position.position.z) / (float)INT64_MAX
            };
            this->DrawPlanet(graphics, p, glm::vec3(s, s, s), color);
            num++;
        }
    }
    LOG("We've drawn " << std::to_string(num) << " entities.");
    LOGENDL();
    LOGENDL();
}

void GameScene::DrawPlanet(gr::Graphics& graphics, glm::vec3 center, glm::vec3 size, glm::vec3 color) const {
    glm::vec2 c = glm::vec2 {center.x, center.y}; // 2D center
    glm::vec2 hs = glm::vec2 {(size.x * 0.5f) * (1/std::abs(center.z)), (size.y * 0.5f) * (1/std::abs(center.z))}; // 2D size

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
