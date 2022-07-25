#include "Graphics.hpp"

namespace gr {

Graphics::Graphics() :
instance(mainWindow.getWindow()),
physicalDevice(this->instance),
device(this->physicalDevice),
swapChain(this->device.getDevice(), this->physicalDevice, this->instance, static_cast<uint32_t>(mainWindow.getWidth()), static_cast<uint32_t>(mainWindow.getHeight())),
pipeline(this->instance, this->device, this->swapChain, this->physicalDevice)
{
}

Graphics::~Graphics()
{
}

void Graphics::test()
{
    this->pipeline.drawFrame();
}

void Graphics::waitForIdle() {
    vkDeviceWaitIdle(this->device.getDevice());
}

Buffer &Graphics::newBuffer(size_t nvertex)
{
    return this->pipeline.newBuffer(nvertex);
}

void Graphics::removeBuffer(Buffer &b)
{
    this->pipeline.removeBuffer(b);
}

}