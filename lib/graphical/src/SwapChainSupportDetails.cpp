#include "SwapChainSupportDetails.hpp"

namespace gr {

bool SwapChainSupportDetails::isComplete() const
{
    return !this->formats.empty() && !this->presentModes.empty();
}

}