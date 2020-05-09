//
// Created by adrien on 01/02/20.
//

#ifndef INC_71K2LEDEB_TEXTURE_H
#define INC_71K2LEDEB_TEXTURE_H

#include <iostream>
#include "glad.h"
#include "GL/gl.h"
#include "stb_image.h"

#define MAX_TEXTURE 32

class Texture
{
private:
    std::string     _filePath;
    unsigned char   *_localBuffer;
    int             _width;
    int             _height;
    int             _bitsPerPixel;
    inline static unsigned int    _textureId = 0;

public:
    unsigned int    _mRenderer;

public:
    Texture(const std::string &);
    Texture(int, int);
    ~Texture();

    void    initImageTexture();
    void    initDepthTexture();
    void    genTexture();
    unsigned int bind();
    void unbind() const;
};

#endif //INC_71K2LEDEB_TEXTURE_H
