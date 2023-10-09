#pragma once

#include "SD_PCH.h"


namespace Soda
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~Shader();

        virtual void Bind();
        virtual void Unbind();

    private:
        uint32_t m_ShaderID;
    };
}