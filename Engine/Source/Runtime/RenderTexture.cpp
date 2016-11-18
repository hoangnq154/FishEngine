#include "RenderTexture.hpp"
#include "Debug.hpp"

namespace FishEngine
{

    RenderTexture::~RenderTexture()
    {
        glDeleteFramebuffers(1, &m_FBO);
    }

    RenderTexturePtr RenderTexture::CreateShadowMap()
    {
        auto rt = std::make_shared<RenderTexture>();
        rt->m_width = 4096;
        rt->m_height = 4096;
        rt->m_format = RenderTextureFormat::Shadowmap;

        glGenFramebuffers(1, &rt->m_FBO);
        glGenTextures(1, &rt->m_texture);
        glBindTexture(GL_TEXTURE_2D, rt->m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
            rt->m_width, rt->m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindFramebuffer(GL_FRAMEBUFFER, rt->m_FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, rt->m_texture, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return rt;
    }

    RenderTexturePtr RenderTexture::CreateColorMap(const int width, const int height)
    {
        auto rt = std::make_shared<RenderTexture>();
        rt->m_width = width;
        rt->m_height = height;
        rt->m_format = RenderTextureFormat::ARGB32;

        
        //glGenRenderbuffers(1, &rt->m_texture);
        //glBindRenderbuffer(GL_RENDERBUFFER, rt->m_texture);
        //glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, rt->m_width, rt->m_height);

        glGenFramebuffers(1, &rt->m_FBO);
        glGenTextures(1, &rt->m_texture);
        glBindTexture(GL_TEXTURE_2D, rt->m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rt->m_width, rt->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glGenTextures(1, &rt->m_depthBuffer);
        glBindTexture(GL_TEXTURE_2D, rt->m_depthBuffer);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, rt->m_width, rt->m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, rt->m_width, rt->m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindFramebuffer(GL_FRAMEBUFFER, rt->m_FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rt->m_texture, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, rt->m_depthBuffer, 0);
        //glDrawBuffer(GL_NONE);
        //glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return rt;
    }

    void RenderTexture::Resize(const int newWidth, const int newHeight)
    {
        Debug::Log("RenderTexture::Resize");
        m_width = newWidth;
        m_height = newHeight;
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, m_depthBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    }

} // namespace FishEngine