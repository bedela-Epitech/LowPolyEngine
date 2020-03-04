//
// Created by adrien on 21/02/20.
//

#ifndef INC_71K2LEDEB_ERRORMANAGER_H
#define INC_71K2LEDEB_ERRORMANAGER_H

#include "glad.h"
#include <GL/gl.h>
#include <iostream>

#define ASSERT(x) if (!(x));
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

#endif //INC_71K2LEDEB_ERRORMANAGER_H
