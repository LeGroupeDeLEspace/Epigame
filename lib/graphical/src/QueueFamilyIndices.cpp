#include "QueueFamilyIndices.hpp"

namespace gr {

bool QueueFamilyIndices::isComplete()
{
    return graphicsFamily.has_value() && presentFamily.has_value();
}

}