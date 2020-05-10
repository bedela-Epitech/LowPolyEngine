//
// Created by adrien on 03/01/20.
//

#ifndef _L_OPENGL_H_

#define _L_OPENGL_H_

#include <future>
#include "map/Terrain.h"
#include "encapsulation/Menu.h"
#include "encapsulation/FrameBuffer.h"

class L_OpenGL
{
public:
    FrameBuffer             _fbo;
    std::thread             _loadingThread;
    Terrain                 _terrain;
    std::shared_ptr<Menu>   _menu;

public:
    L_OpenGL(const std::string &, const std::string &,
             const std::shared_ptr<Menu> &);

    void    initShader(const glm::mat4 &);
    void    updateShader(const glm::vec3 &, const glm::mat4 &);
    void    display();
};

#endif // _L_OPENGL_H_
