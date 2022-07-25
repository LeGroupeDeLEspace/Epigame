//
// Created by Iannis on 19/07/2022.
//

#ifndef JEUDELESPACE_GAMESCENE_HPP
#define JEUDELESPACE_GAMESCENE_HPP

#include "scene/Scene.hpp"
#include "utils/Command.hpp"
#include "utils/DataContainer.hpp"
#include "generation/UniversalPosition.hpp"
#include "generation/Universe.hpp"
#include <entt/entt.hpp>

class OnMove : public Command1<DataContainer *> {
private:
    glm::vec3& movement;
public:
    explicit OnMove(glm::vec3& movement);
    ~OnMove() override;
    void execute(DataContainer * value) override;
};


class GameScene : public Scene {
private:
    entt::registry registry;
    entt::entity player;
    glm::vec3 movement;
    UniversalPosition universalPosition;
    OnMove onMoveCommand;

    bool shouldUpdate;
public:
    GameScene();
    void OnCreate() override;
    void OnDestroy() override;
    void OnActivate() override;
    void OnDeactivate() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Draw(GLFWwindow& window) override;

    void DrawUniverse() const;
};


#endif //JEUDELESPACE_GAMESCENE_HPP
