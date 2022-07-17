//
// Created by ianpo on 16/07/2022.
//

#ifndef JEUDELESPACE_CHARACTERCONTROLLER_HPP
#define JEUDELESPACE_CHARACTERCONTROLLER_HPP

#include "ICharacterController.hpp"

class CharacterController : public ICharacterController {
private:
    bool status;
public:
    void enable() override;
    virtual void update() override = 0;
    void disable() override;
    bool isEnable() override;
};


#endif //JEUDELESPACE_CHARACTERCONTROLLER_HPP
