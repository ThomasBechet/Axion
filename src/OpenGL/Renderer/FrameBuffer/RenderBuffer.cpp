#include <OpenGL/Renderer/FrameBuffer/RenderBuffer.hpp>

#include <Core/Context/Engine.hpp>

using namespace ax;

RenderBuffer::RenderBuffer(Vector2u dimension)
{
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glGenTextures(1, &m_renderTexture);
    glBindTexture(GL_TEXTURE_2D, m_renderTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, dimension.x, dimension.y, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderTexture, 0);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(Status != GL_FRAMEBUFFER_COMPLETE){
        Engine::interrupt("Failed to load renderbuffer");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
RenderBuffer::~RenderBuffer()
{
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteTextures(1, &m_renderTexture);
}

void RenderBuffer::bindForWriting() const noexcept
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, buffers);
}
void RenderBuffer::bindForReading() const noexcept
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_renderTexture);
}
void RenderBuffer::clear(Color3 color) const noexcept
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    glClearColor(color.r, color.g, color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}