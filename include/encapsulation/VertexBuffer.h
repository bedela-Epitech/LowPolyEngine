//
// Created by adrien on 17/02/20.
//

#ifndef INC_71K2LEDEB_VERTEXBUFFER_H
#define INC_71K2LEDEB_VERTEXBUFFER_H

#include <glad/glad.h>
#include <vector>
#include <iostream>
#include <type_traits>

class VertexArray;

struct Element
{
    int             location;
    unsigned int    count;
    int             type;
    bool            normalized;
};

class Layout
{
private:
    std::vector<Element>    _elements;
    unsigned int            _size;
    unsigned int            _shaderID;

public:
    Layout(unsigned int);

    friend VertexArray;

    template <typename T>
    void addElement(const char *, unsigned int, bool);
};

class VertexBuffer
{
private:
    unsigned int _rendererId;
public:
    VertexBuffer(const void *, unsigned int);
    ~VertexBuffer();

    void bind();
    void unbind();
};

#endif //INC_71K2LEDEB_VERTEXBUFFER_H
