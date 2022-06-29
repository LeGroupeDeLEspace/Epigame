#include "Logger.hpp"
#include "ErrorTracking.hpp"
#include <iostream>

int main()
{
    Logger::log(WARNING, "ici une erreur", ERR_LOCATION);
    return 0;
}