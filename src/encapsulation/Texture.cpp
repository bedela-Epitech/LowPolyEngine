//
// Created by adrien on 01/02/20.
//

#include "encapsulation/Texture.h"

Texture::Texture(const std::string &filepPath)
: _filePath(filepPath), _mRenderer(0)
{
    stbi_set_flip_vertically_on_load(1);
    _localBuffer = stbi_load(filepPath.c_str(), &_width, &_height, &_bitsPerPixel, 4);

    glGenTextures(1, &_mRenderer);
    glBindTexture(GL_TEXTURE_2D, _mRenderer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (_localBuffer)
        stbi_image_free(_localBuffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_mRenderer);
}

unsigned int    Texture::bind()
{
    if (_textureId >= MAX_TEXTURE)
        throw std::out_of_range("too much textures");

    glActiveTexture(GL_TEXTURE0 + _textureId);
    glBindTexture(GL_TEXTURE_2D, _mRenderer);

    _textureId++;
    return _textureId - 1;
}

void        Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}