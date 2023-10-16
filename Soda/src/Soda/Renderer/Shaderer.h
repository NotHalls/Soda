#pragma once

#include "SD_PCH.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace Soda
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~Shader();

        void Bind();
        void Unbind();

        void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        uint32_t m_ShaderID;
    };
}