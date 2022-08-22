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
#include "Shapes/ShapeBase.hpp"
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
        universalPosition(50),
        onMoveCommand(this->movement),
        shouldUpdate(false) {}

void GameScene::OnCreate() {
    player = registry.create();
    registry.emplace<UniversalPosition>(player, this->universalPosition);
    registry.emplace<Rotation>(player, glm::dquat{0,0,0,1});

    auto ss = SolarSystem(universalPosition);
    auto bodies = Universe::getCelestialBodies(universalPosition, VIEW_DISTANCE);
    for (auto& cb: bodies) {
        try {
            const auto body = registry.create();
//            auto lp = LocalPosition::createLocalPosition(this->universalPosition, cb.position);
//            registry.emplace<LocalPosition>(body, lp);
            registry.emplace<UniversalPosition>(body, cb.position);
            registry.emplace<Size>(body, cb.size);
            glm::vec3 c = glm::vec3 {
                    (long double)cb.position.position.x /(long double)INT_MAX,
                    (long double)cb.position.position.y /(long double)INT_MAX,
                    (long double)cb.position.position.z /(long double)INT_MAX,
            };

            c *= 0.5f;
            c += 0.5f;
            registry.emplace<Color>(body, c);
        } catch (std::runtime_error& e) {
            continue;
        }
    }
    shouldUpdate = true;
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
        auto view = registry.view<UniversalPosition, Size>();
        // Checking for each entity that they are not outside the new position
        for(auto [entity, pos, size]: view.each()) {
//            auto cbPos = pos.getGlobalPosition(this->universalPosition);
            try {
                auto lp = LocalPosition::createLocalPosition(newPos, pos);
            } catch (std::runtime_error& e) {
                registry.destroy(entity);
                continue;
            }
        }
        universalPosition = newPos;
        registry.replace<UniversalPosition>(player, this->universalPosition);
    }
}

void GameScene::LateUpdate(float deltaTime) {
    if(glm::vec3{0,0,0} != movement) {
        auto view = registry.view<UniversalPosition, Size>();
        auto bodies = Universe::getCelestialBodies(universalPosition, VIEW_DISTANCE);
        for (auto& cb: bodies) {
            bool stop = false;
            for (auto [entity, pos, size]: view.each()) {
                if(cb.position == pos) {
                    stop = true;
                    break;
                }
            }
            if(stop) continue;

            const auto body = registry.create();
//            LocalPosition lp = LocalPosition::createLocalPosition(universalPosition, cb.position);
//            registry.emplace<LocalPosition>(body, lp);
            registry.emplace<UniversalPosition>(body, cb.position);
            registry.emplace<Size>(body, cb.size);
            glm::dvec3 c = glm::dvec3 {
                    (long double)cb.position.position.x /(long double)INT_MAX,
                    (long double)cb.position.position.y /(long double)INT_MAX,
                    (long double)cb.position.position.z /(long double)INT_MAX,
            };

            c *= 0.5f;
            c += 0.5f;
            registry.emplace<Color>(body, c);
            LOGENDL();
        }
//        movement = glm::vec3();
    }
}

void GameScene::Draw(gr::Graphics& graphics) {
    if(shouldUpdate) {
        graphics.clearBuffer();
        DrawUniverse(graphics);
        shouldUpdate = false;
    }
}

void GameScene::DrawUniverse(gr::Graphics& graphics) const {
    graphics.shapesManager.clear();
    auto view = registry.view<UniversalPosition, Size, Color>();
    auto position = registry.get<UniversalPosition>(player);

    // To only show what's in front of us.
    auto direction = glm::dvec3{0,0,1};
    auto rotation = registry.get<Rotation>(player).value;

    // Multiply Quaternion by vector
    auto xyz = glm::dvec3{rotation.x,rotation.y,rotation.z};
    auto t = 2.0 * glm::cross(xyz, direction);
    direction = direction +  rotation.w * t + glm::cross(xyz, t);
    // End of Multiplication

    int num = 0;
    auto cbs = std::vector<gr::ShapeBase*>();
    cbs.reserve(view.size_hint());
    for (auto [entity, pos, size, color]: view.each()) {
        auto lp = LocalPosition::createLocalPosition(position, pos);
        glm::dvec3 p = glm::dvec3{
                (long double)lp.value.x/(long double)VIEW_DISTANCE,
                (long double)lp.value.y/(long double)VIEW_DISTANCE,
                (long double)lp.value.z/(long double)VIEW_DISTANCE
        };

        float s = size.value / 50.0;
        if(glm::dot(glm::normalize(direction), glm::normalize(p)) > 0) {
            cbs.push_back(this->DrawPlanet(graphics, p, s, color.value));
            num++;
        }
    }

    if(!cbs.empty()) {
        graphics.shapesManager.loadShapes(cbs);
    }

    for (auto cb: cbs) {
        delete cb;
    }

    LOG("We've drawn " << std::to_string(num) << " entities.");
    LOGENDL();
    LOGENDL();
}

gr::ShapeBase* GameScene::DrawPlanet(gr::Graphics& graphics, glm::vec3 center, float size, glm::vec3 color) const {
    glm::vec2 c = glm::vec2 {center.x, center.y}; // 2D center
    float hs = size * (1/std::abs(center.z)); // 2D size
    auto* shape = new gr::CircleShape(c,hs,20);
    shape->setColor(color);
    return shape;

//    // Vertices of the rectangle
//    std::vector<gr::Vertex> vertices = {
//            {{c.x-hs, c.y-hs}, color},
//            {{c.x+hs, c.y - hs}, color},
//            {{c.x - hs, c.y + hs}, color},
//            {{c.x + hs, c.y + hs}, color},
//    };
//
//    // Indexes to make a rectangle
//    std::vector<uint16_t> index = {
//            0, 1, 2, 2, 1, 3,
//    };
//
//    gr::Buffer& buffer = graphics.newBuffer(4, 6); // for a rectangle
//    buffer.copyData(vertices.data());
//    buffer.copyIndexData(index.data());
}

OnMove::OnMove(glm::vec3& movement) : movement(movement) {

}

OnMove::~OnMove() {

}

void OnMove::execute(DataContainer* value) {
    movement = value->getVec3();
}
