//
// Created by bedela on 10/05/2020.
//

#include "encapsulation/GUI.h"

GUI::GUI(const std::string &textureVsPath, const std::string &textureFsPath,
         const glm::vec2 &pos, const glm::vec2 &size)
: _textShader(textureVsPath, textureFsPath), _bufferLayout(_textShader.ID)
{
    _textShader.use();

    try {
        _bufferLayout.addElement<float>("aPos", 2, GL_FALSE);
        _bufferLayout.addElement<float>("textCoord", 2, GL_FALSE);
    }
    catch (const std::invalid_argument &error) {
        throw std::invalid_argument("in GUI, invalid shader variable name");
    }

    initTexture(pos, size);
}

void    GUI::initTexture(const glm::vec2 &pos, const glm::vec2 &size)
{

    _textVertices = {
            pos.x,          pos.y,          0.f, 0.f,
            pos.x + size.x, pos.y,          1.f, 0.f,
            pos.x + size.x, pos.y + size.y, 1.f, 1.f,

            pos.x,          pos.y + size.y, 0.f, 1.f,
            pos.x,          pos.y,          0.f, 0.f,
            pos.x + size.x, pos.y + size.y, 1.f, 1.f,
    };

    _vertexNb = _textVertices.size() / 2;

    linkTextureInfo();
}

void    GUI::linkTextureInfo()
{
    _vArray.addVertexBuffer(_textVertices.data(), sizeof(float) * _textVertices.size(), _bufferLayout);
}

void GUI::attachTexture(const Texture &texture)
{
    Texture::unbind();
    texture.bind();
    _textShader.use();
    _textShader.setInt("u_Texture", texture._textureId);
}

void    GUI::draw() const
{
    GLCall(glBindVertexArray(_vArray._vArrayId));
    GLCall(glDrawArrays(GL_TRIANGLES, 0, _vertexNb));
}