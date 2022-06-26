#include "Graphics.hpp"

namespace gr {

Graphics::Graphics() :
windowHandler(nullptr),
instance(nullptr)
{
    try {
        this->windowHandler = new WindowHandler;
        this->instance = new VulkanInstance(this->windowHandler->getWindow());
    }
    catch (const std::exception &exception) {
        this->~Graphics();
        throw exception;
    }
}

Graphics::~Graphics()
{
    delete this->instance;
    delete this->windowHandler;
}

GLFWwindow *Graphics::getWindow()
{
    return this->windowHandler->getWindow();
}

}