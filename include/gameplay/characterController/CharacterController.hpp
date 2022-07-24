//
// Created by ianpo on 16/07/2022.
//

#ifndef JEUDELESPACE_CHARACTERCONTROLLER_HPP
#define JEUDELESPACE_CHARACTERCONTROLLER_HPP

class CharacterController {
private:
    bool status;
public:
    void enable();
    void update();
    void disable();
    bool isEnable();
};


#endif //JEUDELESPACE_CHARACTERCONTROLLER_HPP
