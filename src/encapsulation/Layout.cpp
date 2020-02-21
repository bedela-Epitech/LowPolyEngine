//
// Created by adrien on 20/02/20.
//

#include "encapsulation/VertexBuffer.h"

Layout::Layout(unsigned int shaderID)
: _shaderId(shaderID)
{ }

template <typename T>
void Layout::addElement(const char *name, unsigned int count, bool normalized)
{
    std::cout << _shaderId << std::endl;
    auto pos = glGetAttribLocation(_shaderId, name);
    if (pos < 0)
        throw ("unvalid location");

    if constexpr (std::is_same<T, float>::value)
        _elements.push_back({pos, count, GL_FLOAT, normalized});
    if constexpr (std::is_same<T, unsigned int>::value)
        _elements.push_back({pos, count, GL_UNSIGNED_INT, normalized});

    _size += count * sizeof(T);
}

template void Layout::addElement<float>(const char *, unsigned int , bool);
template void Layout::addElement<unsigned int>(const char *, unsigned int , bool);
