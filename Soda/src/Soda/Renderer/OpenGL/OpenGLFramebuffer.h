#pragma once

#include "Soda/Renderer/Framebuffer.h"



namespace Soda
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferInfo& framebufferInfo);
        virtual ~OpenGLFramebuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetFrameTextureID() const override
        { return m_FrameTextureID; }
        
    private:
        void Refresh();
    private:
        uint32_t m_FramebufferID;
        uint32_t m_FrameTextureID;
        uint32_t m_DepthBufferID;

        FramebufferInfo m_FramebufferInfo;
    };
}