#include "Graphics.hpp"

namespace gr {

Graphics::Graphics() :
instance(nullptr)
{
    try {
        this->windowHandler = new WindowHandler;
        this->instance = new VulkanInstance;
    }
    catch (const std::exception &exception) {
        this->~Graphics();
        throw exception;
    }
}

Graphics::~Graphics()
{
    delete this->instance;
}

GLFWwindow *Graphics::getWindow()
{
    return this->windowHandler->getWindow();
}

}