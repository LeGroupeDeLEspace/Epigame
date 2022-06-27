//
// Created by Iannis on 27/06/2022.
//

#include "Inputs/DataContainer.hpp"
#include <stdexcept>

// Helper
size_t DataTypeHelper::getDataTypeSize(DataType type) {
    switch (type) {
        case Bool:
            return sizeof(bool);
        case Float:
            return sizeof(float);
        case Int:
            return sizeof(int);
        case Vec2:
            return sizeof(float)*2;
        case Vec2Int:
            return sizeof(int)*2;
        case Vec3:
            return sizeof(float)*3;
        case Vec3Int:
            return sizeof(int)*3;
        case Vec4:
            return sizeof(float)*4;
        case Vec4Int:
            return sizeof(int)*4;
        default:
            throw std::runtime_error(std::string("The DataType ")
                                             .append(std::to_string(type))
                                             .append(" is not implemented."));
    }
}

std::string DataTypeHelper::toString(DataType type) {
    switch (type) {
        case Float:
            return "Float";
        case Int:
            return "Integer";
        case Vec2:
            return "Vector2";
        case Vec2Int:
            return "Vector2 Int";
        case Vec3:
            return "Vector3";
        case Vec3Int:
            return "Vector3 Int";
        case Vec4:
            return "Vector4";
        case Vec4Int:
            return "Vector4 int";
        case Bool:
            return "Boolean";
        default:
            throw std::runtime_error(std::string("The DataType ")
                                             .append(std::to_string(type))
                                             .append(" is not implemented."));

    }
}


// Constructor / Destructor
DataContainer::DataContainer(DataType type): size(DataTypeHelper::getDataTypeSize(type)), type(type) {
    this->data = operator new(size);

    // Initializing my data
    unsigned char *ptr = (unsigned char *)this->data;
    size_t len = this->size;
    while (len-- > 0) *ptr++ = 0;
}

DataContainer::~DataContainer() {
    operator delete (this->data);
}


// Set Data
void DataContainer::setData(bool value) {
    if(type != DataType::Bool) {
        throw std::runtime_error("Cannot set the Boolean value as this object contain a " + DataTypeHelper::toString(type));
    }

    *((bool*)this->data) = value;
}

void DataContainer::setData(int value) {
    if (type != DataType::Int) {
        throw std::runtime_error("Cannot set the Integer value as this object contain a " + DataTypeHelper::toString(type));
    }

    *((int*)this->data) = value;
}

void DataContainer::setData(float value) {
    if (type != DataType::Float) {
        throw std::runtime_error("Cannot set the Float value as this object contain a " + DataTypeHelper::toString(type));
    }

    *((float*)this->data) = value;
}

void DataContainer::setData(int x, int y) {
    if (type != DataType::Vec2Int) {
        throw std::runtime_error("Cannot set the Vector2 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[0] = x;
    ((int*)this->data)[1] = y;
}

void DataContainer::setData(glm::ivec2 value) {
    this->setData(value.x, value.y);
}

void DataContainer::setData(float x, float y) {
    if (type != DataType::Vec2) {
        throw std::runtime_error("Cannot set the Vector2 value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[0] = x;
    ((float*)this->data)[1] = y;
}

void DataContainer::setData(glm::vec2 value) {
    this->setData(value.x, value.y);
}

void DataContainer::setData(int x, int y, int z) {
    if (type != DataType::Vec3Int) {
        throw std::runtime_error("Cannot set the Vector3 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[0] = x;
    ((int*)this->data)[1] = y;
    ((int*)this->data)[2] = z;
}

void DataContainer::setData(glm::ivec3 value) {
    this->setData(value.x, value.y, value.z);
}

void DataContainer::setData(float x, float y, float z) {
    if (type != DataType::Vec3) {
        throw std::runtime_error("Cannot set the Vector3 value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[0] = x;
    ((float*)this->data)[1] = y;
    ((float*)this->data)[2] = z;
}

void DataContainer::setData(glm::vec3 value) {
    this->setData(value.x, value.y, value.z);
}

void DataContainer::setData(int x, int y, int z, int w) {
    if (type != DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Vector4 int value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[0] = x;
    ((int*)this->data)[1] = y;
    ((int*)this->data)[2] = z;
    ((int*)this->data)[3] = w;
}

void DataContainer::setData(glm::ivec4 value) {
    this->setData(value.x, value.y, value.z, value.w);
}

void DataContainer::setData(float x, float y, float z, float w) {
    if (type != DataType::Vec4) {
        throw std::runtime_error("Cannot set the Vector4 value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[0] = x;
    ((float*)this->data)[1] = y;
    ((float*)this->data)[2] = z;
    ((float*)this->data)[3] = w;
}

void DataContainer::setData(glm::vec4 value) {
    this->setData(value.x, value.y, value.z, value.w);
}

// Set one value
void DataContainer::setX(int x) {
    if(type%2 == 0 || type > DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Integer x value as this object is a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[0] = x;
}

void DataContainer::setX(float x) {
    if(type%2 == 1 || type > DataType::Vec4) {
        throw std::runtime_error("Cannot set the Float x value as this object is a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[0] = x;
}

void DataContainer::setY(int y) {
    if(type%2 == 0 || type < DataType::Vec2Int || type > DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Integer Y value as this object is a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[1] = y;
}

void DataContainer::setY(float y) {
    if(type%2 == 1 || type < DataType::Vec2 || type > DataType::Vec4) {
        throw std::runtime_error("Cannot set the Float Y value as this object is a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[1] = y;
}

void DataContainer::setZ(int z) {
    if(type%2 == 0 || type < DataType::Vec3Int || type > DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Integer Z value as this object is a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[2] = z;
}

void DataContainer::setZ(float z) {
    if(type%2 == 1 || type < DataType::Vec3 || type > DataType::Vec4) {
        throw std::runtime_error("Cannot set the Float Z value as this object is a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[2] = z;
}

void DataContainer::setW(int w) {
    if(type != DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Integer W value as this object is a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[3] = w;
}

void DataContainer::setW(float w) {
    if(type != DataType::Vec4) {
        throw std::runtime_error("Cannot set the Float w value as this object is a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[3] = w;
}


// Getter
bool DataContainer::getBool() {
    if(type != DataType::Bool) {
        throw std::runtime_error("Cannot set the Boolean value as this object contain a " + DataTypeHelper::toString(type));
    }

    return *((bool*)this->data);
}

int DataContainer::getInt() {
    if(type != DataType::Int) {
        throw std::runtime_error("Cannot set the Integer value as this object contain a " + DataTypeHelper::toString(type));
    }

    return *((int*)this->data);
}

float DataContainer::getFloat() {
    if(type != DataType::Float) {
        throw std::runtime_error("Cannot set the Float value as this object contain a " + DataTypeHelper::toString(type));
    }

    return *((float*)this->data);
}

glm::ivec2 DataContainer::getVec2Int() {
    if(type != DataType::Vec2Int) {
        throw std::runtime_error("Cannot set the Vector2 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((int*)this->data)[0], ((int*)this->data)[1]};
}

glm::vec2 DataContainer::getVec2() {
    if(type != DataType::Vec2) {
        throw std::runtime_error("Cannot set the Vector2 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((float*)this->data)[0], ((float*)this->data)[1]};
}

glm::ivec3 DataContainer::getVec3Int() {
    if(type != DataType::Vec3Int) {
        throw std::runtime_error("Cannot set the Vector3 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((int*)this->data)[0], ((int*)this->data)[1], ((int*)this->data)[2]};
}

glm::vec3 DataContainer::getVec3() {
    if(type != DataType::Vec3) {
        throw std::runtime_error("Cannot set the Vector3 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((float*)this->data)[0], ((float*)this->data)[1], ((float*)this->data)[2]};
}


glm::ivec4 DataContainer::getVec4Int() {
    if(type != DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Vector4 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((int*)this->data)[0], ((int*)this->data)[1], ((int*)this->data)[2], ((int*)this->data)[3]};
}

glm::vec4 DataContainer::getVec4() {
    if(type != DataType::Vec4) {
        throw std::runtime_error("Cannot set the Vector4 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((float*)this->data)[0], ((float*)this->data)[1], ((float*)this->data)[2], ((float*)this->data)[3]};
}
