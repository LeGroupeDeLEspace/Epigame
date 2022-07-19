//
// Created by Iannis on 18/07/2022.
//

#include <chrono>
#include <thread>
#include <iostream>
#include "Game.hpp"

Game::Game() : frameDuration(DEFAULT_FRAME_DURATION), testWindow(TestWindow::instance()), input(InputManager::instance()) {

}

Game::Game(double frameDuration) : frameDuration(frameDuration), testWindow(TestWindow::instance()), input(InputManager::instance())  {

}

bool Game::isRunning() const {
    return !this->testWindow.shouldClose();
}

void Game::processInputs() {
    this->testWindow.update();
    this->input.update();
}

void Game::update() {

}

void Game::lateUpdate() {

}

void Game::draw() {

}

void Game::waitEndOfFrame(double timePassed) {
    std::cout << "Waiting " << std::to_string(frameDuration - timePassed) << "ms." << std::endl;
    std::this_thread::sleep_for(std::chrono::duration<double,std::milli>(frameDuration-timePassed));
}

