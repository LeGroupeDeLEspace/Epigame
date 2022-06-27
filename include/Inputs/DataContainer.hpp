//
// Created by Iannis on 27/06/2022.
//

#ifndef JEUDELESPACE_DATACONTAINER_HPP
#define JEUDELESPACE_DATACONTAINER_HPP

#include "stdint.h"
#include <string>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

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

namespace DataTypeHelper {
    static std::string toString(DataType type);
    static size_t getDataTypeSize(DataType type);
}

class DataContainer {
public:
    DataContainer(DataType type);
    ~DataContainer();

    void setData(bool value);
    void setData(int value);
    void setData(float value);
    void setData(int x, int y);
    void setData(glm::ivec2 value);
    void setData(float x, float y);
    void setData(glm::vec2 value);
    void setData(int x, int y, int z);
    void setData(glm::ivec3 value);
    void setData(float x, float y, float z);
    void setData(glm::vec3 value);
    void setData(int x, int y, int z, int w);
    void setData(glm::ivec4 value);
    void setData(float x, float y, float z, float w);
    void setData(glm::vec4 value);

    void setX(int x);
    void setX(float x);
    void setY(int y);
    void setY(float y);
    void setZ(int z);
    void setZ(float z);
    void setW(int z);
    void setW(float w);

    bool getBool();
    int getInt();
    float getFloat();
    glm::ivec2 getVec2Int();
    glm::vec2 getVec2();
    glm::ivec3 getVec3Int();
    glm::vec3 getVec3();
    glm::ivec4 getVec4Int();
    glm::vec4 getVec4();
private:
    void * data;
    const DataType type;
    const size_t size;
};

#endif //JEUDELESPACE_DATACONTAINER_HPP
