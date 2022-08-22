#include <algorithm>
#include "ShapesManager.hpp"

namespace gr {

ShapesManager::ShapesManager(Pipeline &pipeline) : pipeline(pipeline)
{
    this->buffer = nullptr;
    this->autoUpdate = false;
}

void ShapesManager::loadShapes(const std::vector<ShapeBase*> &shapes)
{
    this->totalVertices = 0;
    this->totalIndices = 0;
    for (auto &it : shapes) {
        this->shapes.push_back(ShapeRef {it, this->totalVertices, this->totalIndices});
        this->totalVertices += it->getVertexCount();
        this->totalIndices += it->getIndicesCount();
    }

    this->createBuffer();
}

void ShapesManager::createBuffer()
{
    if (this->buffer != nullptr) {
        this->clear();
    }
    this->buffer = &this->pipeline.newBuffer(this->totalVertices, this->totalIndices);

    this->copyDataToBuffer();
}

void ShapesManager::copyDataToBuffer()
{
    //TODO can be reimplemented for better performances but requires to modify Buffer class

    if (this->buffer == nullptr)
        return;

    std::vector<Vertex> tmpVData;
    std::vector<uint16_t> tmpIData;

    for (auto it : shapes) {
        tmpVData.insert(tmpVData.end(), it.shape->getVertices().begin(), it.shape->getVertices().end());
        size_t b = tmpIData.size();
        tmpIData.insert(tmpIData.end(), it.shape->getIndices().begin(), it.shape->getIndices().end());
        std::for_each(tmpIData.begin() + b, tmpIData.end(), [&](uint16_t &i) {
            i += it.vertex_offset;
        });
    }

    this->buffer->copyData(tmpVData.data());
    this->buffer->copyIndexData(tmpIData.data());
}

void ShapesManager::clear()
{
    this->pipeline.removeBuffer(*this->buffer);
    this->buffer = nullptr;
    this->shapes.clear();
}

}