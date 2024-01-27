#pragma once

#include "Soda/Renderer/Shaderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


// EXTREMELY TEMPORARY
typedef unsigned int GLenum;


namespace Soda
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        void Bind() override;
        void Unbind() override;

        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> ProcessSource(const std::string& source);
        void CompileShader(const std::unordered_map<GLenum, std::string>& shaderSources);


        void SetUniformShort(const std::string& name, short value);
        void SetUniformInt(const std::string& name, int value);
		void SetUniformFloat(const std::string& name, float value);

        void SetUniformVec3(const std::string& name, const glm::vec3& vector);
        void SetUniformVec4(const std::string& name, const glm::vec4& vector);
        
        void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        uint32_t m_ShaderID;
    };
}