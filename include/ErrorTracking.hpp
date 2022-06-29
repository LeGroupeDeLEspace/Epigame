#ifndef ERROR_TRACKING_HPP_
#define ERROR_TRACKING_HPP_

#include <string>

#define ERR_LOCATION (std::string(__FILE__).append(":").append(std::to_string(__LINE__)).append(" -> ").append(__FUNCTION__))

#endif