//
// Created by bedela on 08/05/2020.
//

#ifndef LOWPOLYENGINE_FRAMEBUFFER_H
#define LOWPOLYENGINE_FRAMEBUFFER_H

#include "Texture.h"

class FrameBuffer
{
private:
    unsigned int _fbo;
    int         _width;
    int         _height;

    Texture _imageTexture;
    Texture _depthTexture;

public:
    FrameBuffer(bool, bool, int, int);
    ~FrameBuffer();

    void    bind() const;
    void    unbind() const;

private:
    void    attachImageTexture();
    void    attachDepthTexture();
};

#endif //LOWPOLYENGINE_FRAMEBUFFER_H
