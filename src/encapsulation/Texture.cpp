//
// Created by adrien on 01/02/20.
//

#include "encapsulation/Texture.h"

Texture::Texture(const std::string &filepPath)
{
    stbi_set_flip_vertically_on_load(1);
    int bitPerPixel;
    _imageData = stbi_load(filepPath.c_str(), &_width, &_height, &bitPerPixel, 4);

    genTexture();
    bind();
    initImageTexture(_imageData);
    unbind();

    if (_imageData)
        stbi_image_free(_imageData);
}

Texture::Texture(int width, int height)
: _width(width), _height(height)
{}

void Texture::genTexture()
{
    glGenTextures(1, &_mRenderer);
    _textureId = _textureNb;
    _textureNb++;
    if (_textureNb >= MAX_TEXTURE)
        throw std::out_of_range("too much textures");
}

void Texture::initImageTexture(void *data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::initDepthTexture()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_mRenderer);
}

void    Texture::bind() const
{
    glActiveTexture(GL_TEXTURE0 + _textureId);
    glBindTexture(GL_TEXTURE_2D, _mRenderer);
}

void        Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}