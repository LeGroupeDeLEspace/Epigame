#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <chrono>
#include "inputs/InputManager.hpp"
#include "generation/Universe.hpp"
#include "ErrorTracking.hpp"
#include "Logger.hpp"
#include "Game.hpp"

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

int oldMain()
{
    std::cout << "Begin of the project" << std::endl;
    bool result;
    TestWindow & testWindow = TestWindow::instance();
    InputManager & input = InputManager::instance();
    input.addAction(Input::Event::Move, new MovementEvent());
    do {
        testWindow.update();
        input.update();
    } while (!testWindow.shouldClose());

    delete &input;
    return 0;
}

int main()
{
    // Init the game variable
    Game game;

    while (game.isRunning()){
        auto start = std::chrono::system_clock::now();
        // Some computation here
        game.processInputs();
        game.update();
        game.lateUpdate();
        game.draw();
        auto end = std::chrono::system_clock::now();
        // floating-point duration: no duration_cast needed
        std::chrono::duration<double, std::milli> elapsedTime = end - start;

        game.waitEndOfFrame(elapsedTime.count());
    }

    game.graphics.waitForIdle();
    delete &game;

    return 0;
}