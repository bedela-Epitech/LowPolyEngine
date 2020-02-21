//
// Created by adrien on 20/02/20.
//

#include "encapsulation/VertexArray.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &_vArrayId));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &_vArrayId));
}

void VertexArray::addVertexBuffer(const void *data, unsigned int size, const Layout &layout)
{
    unsigned int offset = 0;

    bind();
    _vBuffers.emplace_back(data, size);

    for (const auto &element : layout._elements)
    {
        GLCall(glEnableVertexAttribArray(element.location));
        GLCall(glVertexAttribPointer(element.location, element.count, element.type, element.normalized, layout._size, (const char*)offset));
        offset += element.count * sizeof(element.type);
    }

}
void VertexArray::bind()
{
    GLCall(glBindVertexArray(_vArrayId));
}

void VertexArray::unbind()
{
    GLCall(glBindVertexArray(0));
}