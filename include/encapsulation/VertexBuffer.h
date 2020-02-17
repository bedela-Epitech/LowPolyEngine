//
// Created by adrien on 17/02/20.
//

#ifndef INC_71K2LEDEB_VERTEXBUFFER_H
#define INC_71K2LEDEB_VERTEXBUFFER_H

#include <glad/glad.h>

struct Element
{
    int             location;
    unsigned int    count;
    int             type;
    bool            normalized;
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
