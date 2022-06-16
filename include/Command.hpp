//
// Created by Iannis on 14/06/2022.
//

#ifndef JEUDELESPACE_COMMAND_HPP
#define JEUDELESPACE_COMMAND_HPP

class Command {
public:
    virtual ~Command() { }
    virtual void execute() = 0;
};

#endif //JEUDELESPACE_COMMAND_HPP
