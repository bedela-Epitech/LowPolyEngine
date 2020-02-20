//
// Created by adrien on 20/02/20.
//

#include "encapsulation/VertexBuffer.h"

Layout::Layout(unsigned int shaderID)
: _shaderID(shaderID), _size(0)
{ }

template <typename T>
void Layout::addElement(const char *name, unsigned int count, bool normalized)
{
    auto pos = glGetAttribLocation(_shaderID, name);
    if (pos < 0)
        throw ("unvalid location");

    if constexpr (std::is_same<T, float>::value)
        _elements.emplace_back(pos, count, GL_FLOAT, normalized);
    else if constexpr (std::is_same<T, unsigned int>::value)
        _elements.emplace_back(pos, count, GL_UNSIGNED_INT, normalized);
    else
        throw ("type not supported");

    _size += count * sizeof(T);
}