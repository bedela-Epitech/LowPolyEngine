//
// Created by bedela on 08/05/2020.
//

#include "encapsulation/FrameBuffer.h"

FrameBuffer::FrameBuffer(bool needImage, bool needDepth, int width, int height)
        : _width(width), _height(height)
{
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    if (!needImage && !needDepth)
        throw std::logic_error("FrameBufferObject needs at least one attribute");

    if (!needImage)
        glDrawBuffer(GL_NONE);
    else
        glDrawBuffer(GL_COLOR_ATTACHMENT0);

    if (needDepth)
        attachDepthTexture();
    if (needImage)
        attachImageTexture();

    unbind();
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &_fbo);
}

void FrameBuffer::attachImageTexture()
{
    _imageTexture.bind();
    _imageTexture.initImageTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _imageTexture._mRenderer, 0);
    _imageTexture.unbind();
}

void FrameBuffer::attachDepthTexture()
{
    _depthTexture.bind();
    _depthTexture.initDepthTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture._mRenderer, 0);
    _depthTexture.unbind();
}

void FrameBuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
}

void FrameBuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


