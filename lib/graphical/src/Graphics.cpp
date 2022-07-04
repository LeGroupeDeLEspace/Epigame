#include "Graphics.hpp"

namespace gr {

Graphics::Graphics() :
windowHandler(),
instance(this->windowHandler.getWindow()),
physicalDevice(this->instance),
device(this->physicalDevice),
swapChain(this->device.getDevice(), this->physicalDevice, this->instance, this->windowHandler.getWidth(), this->windowHandler.getHeight()),
renderPass(this->device, this->swapChain)
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