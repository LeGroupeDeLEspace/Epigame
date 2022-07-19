//
// Created by Iannis on 18/07/2022.
//

#include <chrono>
#include <thread>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "Game.hpp"
#include "generation/UniversalPosition.hpp"
#include "generation/Universe.hpp"


#define LOG(s) std::cout << s << std::endl
#define LOGENDL() std::cout << std::endl


class MovementEvent : public Command1<DataContainer *> {
private:
    UniversalPosition position;
    bool isMoving;
public:
    MovementEvent(): position(10,glm::ivec3(10,20,30),glm::ivec3(0,0,0)), isMoving(false){
        displayCurrentSolarSystem();
    }
    ~MovementEvent() override = default;
    void execute(DataContainer * value) override {
        if (isMoving && value->getVec3() == glm::vec3(0,0,0)){
            isMoving = false;
        }
        else if (!isMoving && value->getVec3() != glm::vec3(0,0,0)){
            isMoving = true;
            position.positionSolarSystem += value->getVec3();
            displayCurrentSolarSystem();
        }
    }

    void displayCurrentSolarSystem(){
        auto u = Universe(position.seedUniverse);
        auto g = u.getGalaxy(position.positionGalaxy);
        auto s = g.getSolarSystem(position.positionSolarSystem);

        LOG("We are in the Universe of seed " << std::to_string(position.seedUniverse));
        LOG("We are in the Galaxy " << g.getName() << " at position " << glm::to_string(position.positionGalaxy));
        LOG("We are in the Solar System " << s.getName() << " at position " << glm::to_string(position.positionSolarSystem));
        if (s.exist) {
            LOG(s.getName() << " has " << std::to_string(s.getNumberOfCelestialBodies()) << " Celestial Bodies");
        } else {
            LOG(s.getName() << " isn't really a Solar System. It doesn't even have a sun...");
        }
        LOG("==================================================");
        LOGENDL();

    }
};


Game::Game() : graphics(), frameDuration(DEFAULT_FRAME_DURATION), windowHandler(gr::mainWindow), input(InputManager::instance()) {
    input.addAction(Input::Event::Move, new MovementEvent());
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

