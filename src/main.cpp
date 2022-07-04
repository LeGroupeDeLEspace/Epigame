#include <iostream>
#include "Inputs/InputManager.hpp"
#include "TestWindow.hpp"
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

int main()
{
    std::cout << "Begin of the project" << std::endl;
    bool result;
    TestWindow testWindow = TestWindow::instance();
    InputManager & input = InputManager::instance();
    input.addAction(InputEvent::Move,new DataContainerStateLogger());
    do {
        result = testWindow.update();
        input.update();
    } while (result);

    delete &input;
    return 0;
}
