//
// Created by Iannis on 09/07/2022.
//

#ifndef JEUDELESPACE_UNIVERSE_HPP
#define JEUDELESPACE_UNIVERSE_HPP

#include "Utils/LehmerRandom.hpp"

class Universe {
private:
LehmerRandom rand;
public:
    Universe();
    getSolarSystem(int x, int y, int z);
};


#endif //JEUDELESPACE_UNIVERSE_HPP
