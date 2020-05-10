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
    unsigned char   *_imageData;
    int             _width;
    int             _height;
    inline static unsigned int    _textureNb = 0;

public:
    unsigned int    _mRenderer;
    unsigned int    _textureId;

public:
    Texture(const std::string &);
    Texture(int, int);
    ~Texture();

    void    initImageTexture(void *data = nullptr);
    void    initDepthTexture();
    void    genTexture();
    void    bind() const;
    static void    unbind();
};

#endif //INC_71K2LEDEB_TEXTURE_H
