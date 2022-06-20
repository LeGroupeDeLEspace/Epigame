//
// Created by Iannis on 14/06/2022.
//

#ifndef JEUDELESPACE_COMMAND_HPP
#define JEUDELESPACE_COMMAND_HPP

class Command0 {
public:
    virtual ~Command0() { }
    virtual void execute() = 0;
};

template<typename T1> class Command1 {
public:
    virtual ~Command1() { }
    virtual void execute(T1 value) = 0;
};

template<typename T1, typename T2> class Command2 {
public:
    virtual ~Command2() { }
    virtual void execute(T1 value1, T2 value2) = 0;
};

template<typename T1, typename T2, typename T3> class Command3 {
public:
    virtual ~Command3() { }
    virtual void execute(T1 value1, T2 value2, T3 value3) = 0;
};

#endif //JEUDELESPACE_COMMAND_HPP
