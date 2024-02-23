#include "SD_PCH.h"

#include "Renderer2D.h"
#include "Soda/Renderer/Render.h"

#include "Soda/Renderer/VertexArray.h"
#include "Soda/Renderer/Shaderer.h"
#include "Soda/Renderer/Texture.h"

#include "Soda/Renderer/OpenGL/OpenGLShader.h"


namespace Soda
{
    struct QuadStorage
    {
        std::shared_ptr<VertexArray> m_VA;
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture2D> m_Texture;
    };

    static QuadStorage* m_QuadStorage;


    void Renderer2D::Init()
    {
        m_QuadStorage = new QuadStorage(); // dont worry, we delete this in the Shutdown function
        m_QuadStorage->m_Shader.reset(Shader::Create("assets/shaders/Shader2D.glsl"));
        m_QuadStorage->m_Texture = Texture2D::Create("assets/textures/GingerCat.png");


        m_QuadStorage->m_VA.reset(VertexArray::Create());

        float boxVertices[]
        {
            -0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
             0.5f,  0.5f, 0.0f,		1.0f, 1.0f,	
             0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,		0.0f, 0.0f
        };

        int boxIndices[]
        {
            0, 1, 2,
            0, 2, 3
        };

        std::shared_ptr<VertexBuffer> m_VB;
        m_VB.reset(VertexBuffer::Create(boxVertices, sizeof(boxVertices)));
        m_VB->Bind();
        std::shared_ptr<IndexBuffer> m_IB;
        m_IB.reset(IndexBuffer::Create(boxIndices, 24));
        m_IB->Bind();

        Soda::BufferLoadout Loadout = {
            { "a_position", ShaderDataType::Vec3 },
            { "a_texCoords", ShaderDataType::Vec2 }
        };

        m_VB->SetLoadout(Loadout);

        m_QuadStorage->m_VA->AddVertexBuffer(m_VB);
        m_QuadStorage->m_VA->AddIndexBuffer(m_IB);
    }

    void Renderer2D::Shutdown()
    {
        delete m_QuadStorage;
    }


    void Renderer2D::StartScene(const OrthoCamera& camera)
    {
        Renderer::StartScene(camera);

        m_QuadStorage->m_Shader->Bind();
    }

    void Renderer2D::StopScene()
    {
        Renderer::StopScene();
    }


    void Renderer2D::DrawQuad(const glm::vec2& position, const float& rotation, const glm::vec2& scale, const glm::vec4& color, int zIndex)
    {
        Renderer2D::DrawQuad({ position.x, position.y, zIndex * 0.1 }, rotation, scale, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const float& rotation, const glm::vec2& scale, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

        Renderer::PushThis(m_QuadStorage->m_VA, m_QuadStorage->m_Shader, transform);

        std::dynamic_pointer_cast<OpenGLShader>(m_QuadStorage->m_Shader)->SetUniformVec4("u_Color", color);
        std::dynamic_pointer_cast<OpenGLShader>(m_QuadStorage->m_Shader)->SetUniformMat4("u_ModelMat", transform);
    }
}