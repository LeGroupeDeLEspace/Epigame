//
// Created by Iannis on 18/07/2022.
//

#include <chrono>
#include <thread>
#include <iostream>
#include "Game.hpp"

Game::Game() : graphics(), frameDuration(DEFAULT_FRAME_DURATION), windowHandler(gr::mainWindow), input(InputManager::instance()) {

}

Game::Game(double frameDuration) : graphics(), frameDuration(frameDuration), windowHandler(gr::mainWindow), input(InputManager::instance())  {

}

bool Game::isRunning() const {
    return !glfwWindowShouldClose(this->windowHandler.getWindow());
}

void Game::processInputs() {
    if(isRunning()){
        glfwPollEvents();
    }

    this->input.update();
}

void Game::update() {

}

void Game::lateUpdate() {

}

void Game::draw() {
    graphics.test();
}

void Game::waitEndOfFrame(double timePassed) {
//    std::cout << "Waiting " << std::to_string(frameDuration - timePassed) << "ms." << std::endl;
    std::this_thread::sleep_for(std::chrono::duration<double,std::milli>(frameDuration-timePassed));
}

