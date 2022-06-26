#include "Graphics.hpp"

namespace gr {

Graphics::Graphics() :
windowHandler(),
instance(this->windowHandler.getWindow()),
physicalDevice(this->instance)
{
}

Graphics::~Graphics()
{
}

GLFWwindow *Graphics::getWindow()
{
    return this->windowHandler.getWindow();
}

}