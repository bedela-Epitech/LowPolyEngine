//
// Created by adrien on 21/02/20.
//

#include "encapsulation/ErrorManager.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "OpengGL Error : " << error
                  << ", function" << function << ", file : "
                  << file << ", line : " << line << std::endl;
        return false;
    }
    return true;
}
