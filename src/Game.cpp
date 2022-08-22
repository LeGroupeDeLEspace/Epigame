//
// Created by Iannis on 18/07/2022.
//

#include <chrono>
#include <thread>
#include "Game.hpp"
#include "gameplay/GameScene.hpp"

Game::Game() :
    graphics(),
    frameDuration(DEFAULT_FRAME_DURATION),
    windowHandler(gr::mainWindow),
    input(InputManager::instance()),
    sceneStateMachine()
{
    std::shared_ptr<GameScene> gameScene = std::make_shared<GameScene>();
    unsigned int gameSceneID = sceneStateMachine.Add(gameScene);
    sceneStateMachine.SwitchTo(gameSceneID);
}

Game::Game(double frameDuration) :
    graphics(),
    frameDuration(frameDuration),
    windowHandler(gr::mainWindow),
    input(InputManager::instance()),
    sceneStateMachine()
{

}

bool Game::isRunning() const {
    return !glfwWindowShouldClose(this->windowHandler.getWindow());
}

void Game::processInputs() {
    if(isRunning()){
        glfwPollEvents();
    }

    this->input.update();
    this->sceneStateMachine.ProcessInput();
}

void Game::update(float deltaTime) {
    sceneStateMachine.Update(deltaTime);
}

void Game::lateUpdate(float deltaTime) {
    sceneStateMachine.LateUpdate(deltaTime);
}

void Game::draw() {
    sceneStateMachine.Draw(this->graphics);
    this->graphics.draw();
}

void Game::waitEndOfFrame(double timePassed) {
//    std::cout << "Waiting " << std::to_string(frameDuration - timePassed) << "ms." << std::endl;
    std::this_thread::sleep_for(std::chrono::duration<double,std::milli>(frameDuration-timePassed));
}

