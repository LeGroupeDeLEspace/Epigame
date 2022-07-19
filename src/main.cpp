#include <chrono>
#include "ErrorTracking.hpp"
#include "Game.hpp"

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