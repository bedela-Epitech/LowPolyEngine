//
// Created by adrien on 17/02/20.
//

#include "encapsulation/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1, &_rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_rendererId);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _rendererId);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

