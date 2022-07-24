#include <iostream>
#include "inputs/InputManager.hpp"
#include "glm/gtx/string_cast.hpp"

class DataContainerStateLogger : public Command1<DataContainer *> {
public:
    DataContainerStateLogger() = default;
    ~DataContainerStateLogger() override = default;
    void execute(DataContainer * value) override{
        switch (value->type) {
            case Bool:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << value->getBool() << std::endl;
                break;
            case Float:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << value->getFloat() << std::endl;
                break;
            case Int:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << value->getInt() << std::endl;
                break;
            case Vec2:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << glm::to_string(value->getVec2()) << std::endl;
                break;
            case Vec2Int:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << glm::to_string(value->getVec2Int()) << std::endl;
                break;
            case Vec3:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << glm::to_string(value->getVec3()) << std::endl;
                break;
            case Vec3Int:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << glm::to_string(value->getVec3Int()) << std::endl;
                break;
            case Vec4:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << glm::to_string(value->getVec4()) << std::endl;
                break;
            case Vec4Int:
                std::cout << "Changing " << value << " of type " << DataTypeHelper::toString(value->type) << " to " << glm::to_string(value->getVec4Int()) << std::endl;
                break;
        }
    }
};

class MovementEvent : public Command1<DataContainer *> {
private:
    bool isMoving = false;
public:
    MovementEvent() = default;
    ~MovementEvent() override = default;
    void execute(DataContainer * value) override {
        if (isMoving && value->getVec3() == glm::vec3(0,0,0)){
            std::cout << "You stop moving." << std::endl;
            isMoving = false;
        }
        else if (!isMoving && value->getVec3() != glm::vec3(0,0,0)){
            std::cout << "You start moving." << std::endl;
            isMoving = true;
        }
    }
};
class JumpEvent : public Command1<DataContainer *> {
private:
    Command1<DataContainer *>* p = nullptr;
    bool state = false;
public:
    JumpEvent() = default;
    ~JumpEvent() override = default;

    void execute(DataContainer * value) override {
        if(!value->getBool()) return;

        state = !state;
        if (state) {
            std::cout << "Adding the Movement Event" << std::endl;
            InputManager::instance().addAction(Input::Event::Move, p = new MovementEvent());
        } else {
            std::cout << "Removing the Movement Event" << std::endl;
            InputManager::instance().removeAction(Input::Event::Move,p);
            p = nullptr;
        }
    }
};

int main()
{
    std::cout << "Begin of the project" << std::endl;
    bool result;
    TestWindow testWindow = TestWindow::instance();
    InputManager & input = InputManager::instance();
    input.addAction(Input::Event::Jump, new DataContainerStateLogger());
    input.addAction(Input::Event::Jump, new JumpEvent());
    do {
        result = testWindow.update();
        input.update();
    } while (result);

    delete &input;
    return 0;
}
