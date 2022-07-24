//
// Created by Iannis on 18/07/2022.
//

#ifndef JEUDELESPACE_GAME_HPP
#define JEUDELESPACE_GAME_HPP

#include "inputs/InputManager.hpp"
#include "Graphics.hpp"
#include "WindowHandler.hpp"
#include "scene/SceneStateMachine.hpp"

#define DEFAULT_FRAME_DURATION 16.666

class Game {
public:
    /// The duration of a frame in milliseconds.
    double frameDuration;
    gr::Graphics graphics;
    SceneStateMachine sceneStateMachine;

    Game();
    Game(double frameDuration);
    bool isRunning() const;
    void processInputs();
    void update(float deltaTime);
    void lateUpdate(float deltaTime);
    void draw();
    /// The time that as passed in millisecond;
    void waitEndOfFrame(double timePassed);
    ~Game() = default;
private:
    gr::WindowHandler & windowHandler;
    InputManager & input;
};


#endif //JEUDELESPACE_GAME_HPP
