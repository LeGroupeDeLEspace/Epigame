#include <chrono>
#include <cmath>
#include "Game.hpp"

int main()
{
    // Init the game variable
    Game game;
    double lastFrameDuration;
    while (game.isRunning()){
        auto start = std::chrono::system_clock::now();
        // Some computation here
        game.processInputs();
        game.update((float)std::max<double>(game.frameDuration,lastFrameDuration));
        game.lateUpdate((float)std::max<double>(game.frameDuration,lastFrameDuration));
        game.draw();
        auto end = std::chrono::system_clock::now();

        // floating-point duration: no duration_cast needed
        std::chrono::duration<double, std::milli> elapsedTime = end - start;

        game.waitEndOfFrame(lastFrameDuration=elapsedTime.count());
    }

    game.graphics.waitForIdle();

    return 0;
}