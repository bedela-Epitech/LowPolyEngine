//
// Created by bedela on 10/05/2020.
//

#ifndef LOWPOLYENGINE_GUI_H
#define LOWPOLYENGINE_GUI_H

#include "Texture.h"
#include "encapsulation/Shader.h"
#include "encapsulation/VertexArray.h"

class GUI
{
public:
    Shader              _textShader;
    unsigned int        _vertexNb;
    VertexArray         _vArray;

private:
    Layout              _bufferLayout;
    std::vector<float>  _textVertices;
public:
    GUI(const std::string &, const std::string &,
        const glm::vec2 &, const glm::vec2 &);
    void    attachTexture(const Texture &);
    void    draw() const;

private:
    void    linkTextureInfo();
    void    initTexture(const glm::vec2 &, const glm::vec2 &);
};

#endif //LOWPOLYENGINE_GUI_H
