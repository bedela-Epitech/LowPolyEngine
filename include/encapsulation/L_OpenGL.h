//
// Created by adrien on 03/01/20.
//

#ifndef _L_OPENGL_H_

#define _L_OPENGL_H_

#include "map/Terrain.h"
#include "encapsulation/Menu.h"
#include "encapsulation/ShadowMap.h"

class L_OpenGL
{
public:
    std::shared_ptr<Terrain>    _terrain;
    std::shared_ptr<Menu>       _menu;
    std::shared_ptr<ShadowMap>  _shadowMap;

public:
    L_OpenGL(const std::shared_ptr<Terrain> &,
             const std::shared_ptr<Menu> &,
             const std::shared_ptr<ShadowMap> &);

    void    initShader(const glm::mat4 &);
    void    updateShader(const glm::vec3 &, const glm::mat4 &);
    void    display() const;
    void    clear() const;
};

#endif // _L_OPENGL_H_
