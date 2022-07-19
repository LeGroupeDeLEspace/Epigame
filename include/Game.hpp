//
// Created by Iannis on 18/07/2022.
//

#ifndef JEUDELESPACE_GAME_HPP
#define JEUDELESPACE_GAME_HPP

#include "inputs/InputManager.hpp"
#include "TestWindow.hpp"

#define DEFAULT_FRAME_DURATION 16.666

class Game {
private:
    /// The duration of a frame in milliseconds.
    double frameDuration;
    TestWindow & testWindow;
    InputManager & input;
public:
    Game();
    Game(double frameDuration);
    bool isRunning() const;
    void processInputs();
    void update();
    void lateUpdate();
    void draw();
    /// The time that as passed in millisecond;
    void waitEndOfFrame(double timePassed);
    ~Game() = default;
};


#endif //JEUDELESPACE_GAME_HPP
