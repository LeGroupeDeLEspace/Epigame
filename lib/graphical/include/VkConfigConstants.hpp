#ifndef GR_VK_CONFIG_CONSTANTS_
#define GR_VK_CONFIG_CONSTANTS_

#include <vector>

namespace gr {
namespace config {

extern const char* applicationName;

extern const std::vector<const char*> validationLayers;
extern const std::vector<const char*> deviceExtensions;
extern const bool enableValidationLayers;

extern const int maxFrameInFlight;

}
}

#endif