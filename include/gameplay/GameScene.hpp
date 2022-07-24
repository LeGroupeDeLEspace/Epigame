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

class OnMove : public Command1<DataContainer *> {
private:
    UniversalPosition& universalPosition;
public:
    explicit OnMove(UniversalPosition& universalPosition);
    ~OnMove() override;
    void execute(DataContainer * value) override;
};


class GameScene : public Scene {
private:
    UniversalPosition previousUniversalPosition;
    UniversalPosition universalPosition;
    OnMove onMoveCommand;
public:
    GameScene();
    GameScene(UniversalPosition& universalPosition);
    void OnCreate() override;
    void OnDestroy() override;
    void OnActivate() override;
    void OnDeactivate() override;
    void Draw(GLFWwindow& window) override;

    void DrawUniverse() const;
};


#endif //JEUDELESPACE_GAMESCENE_HPP
