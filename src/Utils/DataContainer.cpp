//
// Created by Iannis on 27/06/2022.
//

#include "Utils/DataContainer.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cstring>

#define LOG(s) std::cout << s << std::endl

#define WRITE(s) std::cout << s

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

std::string DataPropsHelper::toString(Axis props) {
    switch (props) {
        case Axis::None:
            return "None";
        case Axis::X:
            return "X";
        case Axis::Y:
            return "Y";
        case Axis::Z:
            return "Z";
        case Axis::W:
            return "W";
    }
    throw std::runtime_error(std::string("The axis ").append(std::to_string(props)).append(" is not implemented"));
}


// Constructor / Destructor
DataContainer::DataContainer(DataType type): type(type), size(DataTypeHelper::getDataTypeSize(type)), events() {
    this->data = operator new (size);
    // Initializing my data
    for (int i = 0; i < this->size/(sizeof(unsigned char)); ++i) {
        ((unsigned char *)(this->data))[i] = 0;
    }
}

DataContainer::DataContainer(const DataContainer & copy) : DataContainer(copy.type) {
    setData(copy.data);
}

void DataContainer::setData(void * data) {
    memcpy(this->data, data, this->size);
}

DataContainer::DataContainer(bool value):type(DataType::Bool), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    *((bool*)this->data) = value;
}
DataContainer::DataContainer(int value):type(DataType::Int), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    *((int*)this->data) = value;
}
DataContainer::DataContainer(float value):type(DataType::Float), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    *((float*)this->data) = value;}

DataContainer::DataContainer(const glm::ivec2 & value):type(DataType::Vec2Int), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((int*)this->data)[Axis::X] = value.x;
    ((int*)this->data)[Axis::Y] = value.y;
}
DataContainer::DataContainer(int x, int y):type(DataType::Vec2Int), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((int*)this->data)[Axis::X] = x;
    ((int*)this->data)[Axis::Y] = y;
}
DataContainer::DataContainer(const glm::vec2 & value):type(DataType::Vec2), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((float*)this->data)[Axis::X] = value.x;
    ((float*)this->data)[Axis::Y] = value.y;
}
DataContainer::DataContainer(float x, float y):type(DataType::Vec2), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((float*)this->data)[Axis::X] = x;
    ((float*)this->data)[Axis::Y] = y;
}

DataContainer::DataContainer(const glm::ivec3 & value):type(DataType::Vec3Int), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((int*)this->data)[Axis::X] = value.x;
    ((int*)this->data)[Axis::Y] = value.y;
    ((int*)this->data)[Axis::Z] = value.z;
}
DataContainer::DataContainer(int x, int y, int z):type(DataType::Vec3Int), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((int*)this->data)[Axis::X] = x;
    ((int*)this->data)[Axis::Y] = y;
    ((int*)this->data)[Axis::Z] = z;
}
DataContainer::DataContainer(const glm::vec3 & value):type(DataType::Vec3), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((float*)this->data)[Axis::X] = value.x;
    ((float*)this->data)[Axis::Y] = value.y;
    ((float*)this->data)[Axis::Z] = value.z;
}
DataContainer::DataContainer(float x, float y, float z):type(DataType::Vec3), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);

    ((float*)this->data)[Axis::X] = x;
    ((float*)this->data)[Axis::Y] = y;
    ((float*)this->data)[Axis::Z] = z;
}

DataContainer::DataContainer(const glm::ivec4 & value):type(DataType::Vec4Int), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((int*)this->data)[Axis::X] = value.x;
    ((int*)this->data)[Axis::Y] = value.y;
    ((int*)this->data)[Axis::Z] = value.z;
    ((int*)this->data)[Axis::W] = value.w;
}
DataContainer::DataContainer(int x, int y, int z, int w):type(DataType::Vec4Int), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((int*)this->data)[Axis::X] = x;
    ((int*)this->data)[Axis::Y] = y;
    ((int*)this->data)[Axis::Z] = z;
    ((int*)this->data)[Axis::W] = w;
}
DataContainer::DataContainer(const glm::vec4 & value):type(DataType::Vec4), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((float*)this->data)[Axis::X] = value.x;
    ((float*)this->data)[Axis::Y] = value.y;
    ((float*)this->data)[Axis::Z] = value.z;
    ((float*)this->data)[Axis::W] = value.w;
}
DataContainer::DataContainer(float x, float y, float z, float w):type(DataType::Vec4), size(DataTypeHelper::getDataTypeSize(type)),  events() {
    this->data = operator new (size);
    ((float*)this->data)[Axis::X] = x;
    ((float*)this->data)[Axis::Y] = y;
    ((float*)this->data)[Axis::Z] = z;
    ((float*)this->data)[Axis::W] = w;
}

DataContainer::~DataContainer() {

    operator delete (this->data);
    events.clear();
}


// Set Data
void DataContainer::setData(bool value) {
    if(type != DataType::Bool) {
        throw std::runtime_error("Cannot set the Boolean value as this object contain a " + DataTypeHelper::toString(type));
    }

    *((bool*)this->data) = value;

    this->triggerEvents();
}

void DataContainer::setData(int value) {
    if (type != DataType::Int) {
        throw std::runtime_error("Cannot set the Integer value as this object contain a " + DataTypeHelper::toString(type));
    }

    *((int*)this->data) = value;

    this->triggerEvents();
}

void DataContainer::setData(float value) {
    if (type != DataType::Float) {
        throw std::runtime_error("Cannot set the Float value as this object contain a " + DataTypeHelper::toString(type));
    }

    *((float*)this->data) = value;

    this->triggerEvents();
}

void DataContainer::setData(int x, int y) {
    if (type != DataType::Vec2Int) {
        throw std::runtime_error("Cannot set the Vector2 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[Axis::X] = x;
    ((int*)this->data)[Axis::Y] = y;

    this->triggerEvents();
}

void DataContainer::setData(const glm::ivec2 & value) {
    this->setData(value.x, value.y);
}

void DataContainer::setData(float x, float y) {
    if (type != DataType::Vec2) {
        throw std::runtime_error("Cannot set the Vector2 value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[Axis::X] = x;
    ((float*)this->data)[Axis::Y] = y;

    this->triggerEvents();
}

void DataContainer::setData(const glm::vec2 & value) {
    this->setData(value.x, value.y);
}

void DataContainer::setData(int x, int y, int z) {
    if (type != DataType::Vec3Int) {
        throw std::runtime_error("Cannot set the Vector3 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[Axis::X] = x;
    ((int*)this->data)[Axis::Y] = y;
    ((int*)this->data)[Axis::Z] = z;

    this->triggerEvents();
}

void DataContainer::setData(const glm::ivec3 & value) {
    this->setData(value.x, value.y, value.z);
}

void DataContainer::setData(float x, float y, float z) {
    if (type != DataType::Vec3) {
        throw std::runtime_error("Cannot set the Vector3 value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[Axis::X] = x;
    ((float*)this->data)[Axis::Y] = y;
    ((float*)this->data)[Axis::Z] = z;

    this->triggerEvents();
}

void DataContainer::setData(const glm::vec3 & value) {
    this->setData(value.x, value.y, value.z);
}

void DataContainer::setData(int x, int y, int z, int w) {
    if (type != DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Vector4 int value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[Axis::X] = x;
    ((int*)this->data)[Axis::Y] = y;
    ((int*)this->data)[Axis::Z] = z;
    ((int*)this->data)[Axis::W] = w;

    this->triggerEvents();
}

void DataContainer::setData(const glm::ivec4 & value) {
    this->setData(value.x, value.y, value.z, value.w);
}

void DataContainer::setData(float x, float y, float z, float w) {
    if (type != DataType::Vec4) {
        throw std::runtime_error("Cannot set the Vector4 value as this object contain a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[Axis::X] = x;
    ((float*)this->data)[Axis::Y] = y;
    ((float*)this->data)[Axis::Z] = z;
    ((float*)this->data)[Axis::W] = w;

    this->triggerEvents();
}

void DataContainer::setData(const glm::vec4 & value) {
    this->setData(value.x, value.y, value.z, value.w);
}

// Set one value
void DataContainer::setX(int x) {
    if(type%2 == 0 || type > DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Integer x value as this object is a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[Axis::X] = x;

    this->triggerEvents();
}

void DataContainer::setX(float x) {
    if(type%2 == 1 || type > DataType::Vec4) {
        throw std::runtime_error("Cannot set the Float x value as this object is a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[Axis::X] = x;

    this->triggerEvents();
}

void DataContainer::setY(int y) {
    if(type%2 == 0 || type < DataType::Vec2Int || type > DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Integer Y value as this object is a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[Axis::Y] = y;

    this->triggerEvents();
}

void DataContainer::setY(float y) {
    if(type%2 == 1 || type < DataType::Vec2 || type > DataType::Vec4) {
        throw std::runtime_error("Cannot set the Float Y value as this object is a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[Axis::Y] = y;

    this->triggerEvents();
}

void DataContainer::setZ(int z) {
    if(type%2 == 0 || type < DataType::Vec3Int || type > DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Integer Z value as this object is a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[Axis::Z] = z;

    this->triggerEvents();
}

void DataContainer::setZ(float z) {
    if(type%2 == 1 || type < DataType::Vec3 || type > DataType::Vec4) {
        throw std::runtime_error("Cannot set the Float Z value as this object is a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[Axis::Z] = z;

    this->triggerEvents();
}

void DataContainer::setW(int w) {
    if(type != DataType::Vec4Int) {
        throw std::runtime_error("Cannot set the Integer W value as this object is a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[Axis::W] = w;

    this->triggerEvents();
}

void DataContainer::setW(float w) {
    if(type != DataType::Vec4) {
        throw std::runtime_error("Cannot set the Float w value as this object is a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[Axis::W] = w;

    this->triggerEvents();
}


void DataContainer::setValue(float value, Axis axe) {
    if(axe == Axis::None || type == Bool || type % 2 != 0 || type / 2 < axe) {
        throw std::runtime_error("Cannot get the Float " + DataPropsHelper::toString(axe) + " as this object contain a " + DataTypeHelper::toString(type));
    }

    ((float*)this->data)[axe] = value;

    this->triggerEvents();
}

void DataContainer::setValue(int value, Axis axe) {
    if(axe == Axis::None || type == Bool || type % 2 != 1 || (type - 1) / 2 < axe) {
        throw std::runtime_error("Cannot get the Integer " + DataPropsHelper::toString(axe) + " as this object contain a " + DataTypeHelper::toString(type));
    }

    ((int*)this->data)[axe] = value;

    this->triggerEvents();
}

// Getter
bool DataContainer::getBool() {
    if(type != DataType::Bool) {
        throw std::runtime_error("Cannot get the Boolean value as this object contain a " + DataTypeHelper::toString(type));
    }

    return *((bool*)this->data);
}

int DataContainer::getInt() {
    if(type != DataType::Int) {
        throw std::runtime_error("Cannot get the Integer value as this object contain a " + DataTypeHelper::toString(type));
    }

    return *((int*)this->data);
}

float DataContainer::getFloat() {
    if(type != DataType::Float) {
        throw std::runtime_error("Cannot get the Float value as this object contain a " + DataTypeHelper::toString(type));
    }

    return *((float*)this->data);
}

glm::ivec2 DataContainer::getVec2Int() {
    if(type != DataType::Vec2Int) {
        throw std::runtime_error("Cannot get the Vector2 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((int*)this->data)[Axis::X], ((int*)this->data)[Axis::Y]};
}

glm::vec2 DataContainer::getVec2() {
    if(type != DataType::Vec2) {
        throw std::runtime_error("Cannot get the Vector2 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((float*)this->data)[Axis::X], ((float*)this->data)[Axis::Y]};
}

glm::ivec3 DataContainer::getVec3Int() {
    if(type != DataType::Vec3Int) {
        throw std::runtime_error("Cannot get the Vector3 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((int*)this->data)[Axis::X], ((int*)this->data)[Axis::Y], ((int*)this->data)[Axis::Z]};
}

glm::vec3 DataContainer::getVec3() {
    if(type != DataType::Vec3) {
        throw std::runtime_error("Cannot get the Vector3 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((float*)this->data)[Axis::X], ((float*)this->data)[Axis::Y], ((float*)this->data)[Axis::Z]};
}


glm::ivec4 DataContainer::getVec4Int() {
    if(type != DataType::Vec4Int) {
        throw std::runtime_error("Cannot get the Vector4 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((int*)this->data)[Axis::X], ((int*)this->data)[Axis::Y], ((int*)this->data)[Axis::Z], ((int*)this->data)[Axis::W]};
}

glm::vec4 DataContainer::getVec4() {
    if(type != DataType::Vec4) {
        throw std::runtime_error("Cannot get the Vector4 Int value as this object contain a " + DataTypeHelper::toString(type));
    }

    return {((float*)this->data)[Axis::X], ((float*)this->data)[Axis::Y], ((float*)this->data)[Axis::Z], ((float*)this->data)[Axis::W]};
}

float DataContainer::getFloat(Axis axe) {
    if(axe == Axis::None || type == Bool || type % 2 != 0 || type / 2 < axe) {
        throw std::runtime_error("Cannot get the Float " + DataPropsHelper::toString(axe) + " as this object contain a " + DataTypeHelper::toString(type));
    }

    return ((float*)this->data)[axe];
}

int DataContainer::getInt(Axis axe) {
    if(axe == Axis::None || type == Bool || type % 2 != 1 || (type - 1) / 2 < axe) {
        throw std::runtime_error("Cannot get the Integer " + DataPropsHelper::toString(axe) + " as this object contain a " + DataTypeHelper::toString(type));
    }

    return ((int*)this->data)[axe];
}


bool DataContainer::addEvent(DataContainerEvent event) {
    //TODO: check "event" is not a nullptr
    auto it = std::find(events.begin(), events.end(), event);
    if (it == events.end()) {
        events.push_back(event);
        return true;
    }

    // TODO: Log the given events has already been passed.
    return false;
}

bool DataContainer::operator+=(DataContainerEvent event) {
    return this->addEvent(event);
}

bool DataContainer::removeEvent(DataContainerEvent event) {
    //TODO: check "event" is not a nullptr
    auto it = std::find(events.begin(), events.end(), event);
    if (it != events.end()) {
        events.erase(it);
        return true;
    }

    // TODO: Log the given event has never been stored.
    return false;
}

bool DataContainer::operator-=(DataContainerEvent event) {
    return this->removeEvent(event);
}

void DataContainer::triggerEvents() {
    for (DataContainerEvent event: events) {
        if(event == nullptr) {
            // TODO: Log the fact that a null pointer have been sent to the evetns
            continue;
        }

        event(this);
    }
}
