#include "Logger.hpp"
#include "System.hpp"
#include <iostream>

int main()
{
    Logger log;
    log.log(WARNING, "ici une erreur", "la macro de mon poto");
    return 0;
}