//
// Created by bedela on 08/05/2020.
//

#include "encapsulation/FrameBuffer.h"

FrameBuffer::FrameBuffer(const std::string &textVsPath, const std::string &textFsPath,
                         const glm::vec2 &pos, const glm::vec2 &size,
                         bool needImage, bool needDepth, int width, int height)
        : _gui(textVsPath, textFsPath, pos, size),
          _width(width), _height(height), _imageTexture(width, height), _depthTexture(width, height)
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
    {
        attachImageTexture();
        _gui.attachTexture(_imageTexture);
    }

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("FrameBufferObject could not be created");
    unbind();
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &_fbo);
}

void FrameBuffer::attachImageTexture()
{
    _imageTexture.genTexture();
    _imageTexture.bind();
    _imageTexture.initImageTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _imageTexture._mRenderer, 0);
    _imageTexture.unbind();
}

void FrameBuffer::attachDepthTexture()
{
    _depthTexture.genTexture();
    _depthTexture.bind();
    _depthTexture.initDepthTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture._mRenderer, 0);
    _depthTexture.unbind();
}

void FrameBuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glViewport(0, 0, _width, _height);
}

void FrameBuffer::unbind() const
{
    glViewport(0, 0, Window::_windowSize.x, Window::_windowSize.y);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


