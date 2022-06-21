#include "Graphics.hpp"

namespace gr {

Graphics::Graphics() :
instance(nullptr)
{
    try {
        this->instance = new VulkanInstance;
    }
    catch (const std::exception &exception) {
        this->free();
        throw exception;
    }
}

Graphics::~Graphics()
{

}

void Graphics::free()
{
    delete this->instance;
}

}