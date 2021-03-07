//
// Created by adrien on 03/01/20.
//

#ifndef _L_OPENGL_H_

#define _L_OPENGL_H_

#include "map/Terrain.h"
#include "encapsulation/Menu.h"
#include "encapsulation/ShadowMap.h"

class Renderer
{
public:
    std::unique_ptr<Camera>     _camera;
    std::unique_ptr<Terrain>    _terrain;
    std::unique_ptr<Menu>       _menu;
    std::unique_ptr<ShadowMap>  _shadowMap;
    std::unique_ptr<Light>      _light;

public:
    Renderer(std::unique_ptr<Terrain>,
             std::unique_ptr<Menu>,
             std::unique_ptr<ShadowMap>,
             std::unique_ptr<Camera>);

    void    updateShader();
    void    display() const;
    void    clear() const;
};

#endif // _L_OPENGL_H_
