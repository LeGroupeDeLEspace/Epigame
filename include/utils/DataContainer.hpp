//
// Created by Iannis on 27/06/2022.
//

#ifndef JEUDELESPACE_DATACONTAINER_HPP
#define JEUDELESPACE_DATACONTAINER_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "utils/Command.hpp"

enum DataType {
    Float,
    Int,
    Vec2,
    Vec2Int,
    Vec3,
    Vec3Int,
    Vec4,
    Vec4Int,
    Bool,
};

enum Axis {
    None = -1,
    X = 0,
    Y = 1,
    Z = 2,
    W = 3,
};

namespace DataTypeHelper {
    std::string toString(DataType type);
    size_t getDataTypeSize(DataType type);
}

namespace DataPropsHelper {
    std::string toString(Axis);
}


class DataContainer;

using DataContainerEvent = void (*)(DataContainer*);

class DataContainer {
public:
    DataContainer(DataType type);
    DataContainer(const DataContainer & copy);
    explicit DataContainer(bool value);
    explicit DataContainer(int value);
    explicit DataContainer(float value);
    explicit DataContainer(int x, int y);
    explicit DataContainer(const glm::ivec2 & value);
    explicit DataContainer(float x, float y);
    explicit DataContainer(const glm::vec2 & value);
    explicit DataContainer(int x, int y, int z);
    explicit DataContainer(const glm::ivec3 & value);
    explicit DataContainer(float x, float y, float z);
    explicit DataContainer(const glm::vec3 & value);
    explicit DataContainer(int x, int y, int z, int w);
    explicit DataContainer(const glm::ivec4 & value);
    explicit DataContainer(float x, float y, float z, float w);
    explicit DataContainer(const glm::vec4 & value);
    ~DataContainer();

    void setData(bool value);
    void setData(int value);
    void setData(float value);
    void setData(int x, int y);
    void setData(const glm::ivec2 & value);
    void setData(float x, float y);
    void setData(const glm::vec2 & value);
    void setData(int x, int y, int z);
    void setData(const glm::ivec3 & value);
    void setData(float x, float y, float z);
    void setData(const glm::vec3 & value);
    void setData(int x, int y, int z, int w);
    void setData(const glm::ivec4 & value);
    void setData(float x, float y, float z, float w);
    void setData(const glm::vec4 & value);

    void setX(int x);
    void setX(float x);
    void setY(int y);
    void setY(float y);
    void setZ(int z);
    void setZ(float z);
    void setW(int z);
    void setW(float w);

    void setValue(int value, Axis props);
    void setValue(float value, Axis props);

    bool getBool();
    int getInt();
    float getFloat();
    glm::ivec2 getVec2Int();
    glm::vec2 getVec2();
    glm::ivec3 getVec3Int();
    glm::vec3 getVec3();
    glm::ivec4 getVec4Int();
    glm::vec4 getVec4();

    float getFloat(Axis axe);
    int getInt(Axis axe);

    //TODO: make an ID system to store and retrieve the events
    bool addEvent(Command1<DataContainer *> * event);
    bool removeEvent(Command1<DataContainer *> * event);
    bool clearAllEvents();
    bool operator +=(Command1<DataContainer *> * event);
    bool operator -=(Command1<DataContainer *> * event);

    const DataType type;

private:
    const size_t size;
    std::vector<Command1<DataContainer *> *> events;
    void * data;
    void setData(void* data);
    void triggerEvents();
};

#endif //JEUDELESPACE_DATACONTAINER_HPP
