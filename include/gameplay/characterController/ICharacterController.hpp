//
// Created by ianpo on 16/07/2022.
//

#ifndef JEUDELESPACE_ICHARACTERCONTROLLER_HPP
#define JEUDELESPACE_ICHARACTERCONTROLLER_HPP


class ICharacterController {
public:
    virtual void enable() = 0;
    virtual void update() = 0;
    virtual void disable() = 0;

    virtual bool isEnable() = 0;
};


#endif //JEUDELESPACE_ICHARACTERCONTROLLER_HPP
