

#ifndef _L_OPENGL_HPP_

#define _L_OPENGL_HPP_

#include <future>
#include "map/Terrain.h"
#include "encapsulation/Menu.h"
class L_OpenGL
{
public:
    std::thread             _loadingThread;
    Terrain                 _terrain;
    std::shared_ptr<Menu>   _menu;

public:
    L_OpenGL(const std::string &, const std::string &,
             const std::shared_ptr<Menu> &);

    void    initShader(const glm::mat4 &);
    void    updateShader(const glm::vec3 &, const glm::mat4 &);

    void    display();
    void    cleanUp();
};

#endif // _L_OPENGL_HPP_
