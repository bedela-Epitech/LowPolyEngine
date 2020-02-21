//
// Created by adrien on 17/02/20.
//

#include "encapsulation/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    GLCall(glGenBuffers(1, &_rendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &_rendererId));
}

void VertexBuffer::bind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, _rendererId));
}

void VertexBuffer::unbind()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}