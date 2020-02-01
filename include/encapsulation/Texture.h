//
// Created by adrien on 01/02/20.
//

#ifndef INC_71K2LEDEB_TEXTURE_H
#define INC_71K2LEDEB_TEXTURE_H

#include <iostream>
#include "GL/gl.h"
#include "stb_image.h"

class Texture
{
private:
    unsigned int    _mRenderer;
    std::string     _filePath;
    unsigned char   *_localBuffer;
    int             _width;
    int             _height;
    int             _bitsPerPixel;

public:
    Texture(const std::string &);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;
};

#endif //INC_71K2LEDEB_TEXTURE_H
