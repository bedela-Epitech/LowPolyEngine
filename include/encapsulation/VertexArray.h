//
// Created by adrien on 20/02/20.
//

#ifndef INC_71K2LEDEB_VERTEXARRAY_H
#define INC_71K2LEDEB_VERTEXARRAY_H

#include "encapsulation/VertexBuffer.h"

class VertexArray
{
private:
    std::vector<VertexBuffer>   _vBuffers;

public:
    VertexArray();
    void addVertexBuffer(const void *, unsigned int , const Layout &);
};

#endif //INC_71K2LEDEB_VERTEXARRAY_H
