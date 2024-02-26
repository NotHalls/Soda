#include "SD_PCH.h"

#include "Renderer2D.h"
#include "Soda/Renderer/Render.h"

#include "Soda/Renderer/VertexArray.h"
#include "Soda/Renderer/Shaderer.h"
#include "Soda/Renderer/Texture.h"


namespace Soda
{
    struct QuadStorage
    {
        Ref<VertexArray> m_VA;
        Ref<Shader> m_Shader;
        Ref<Texture2D> m_DefaultTexture;
    };

    static QuadStorage* m_QuadStorage;


    void Renderer2D::Init()
    {
        m_QuadStorage = new QuadStorage(); // dont worry, we delete this in the Shutdown function
        m_QuadStorage->m_Shader.reset(Shader::Create("assets/shaders/Shader2D.glsl"));


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

        Ref<VertexBuffer> m_VB;
        m_VB.reset(VertexBuffer::Create(boxVertices, sizeof(boxVertices)));
        m_VB->Bind();
        Ref<IndexBuffer> m_IB;
        m_IB.reset(IndexBuffer::Create(boxIndices, 24));
        m_IB->Bind();

        Soda::BufferLoadout Loadout = {
            { "a_position", ShaderDataType::Vec3 },
            { "a_texCoords", ShaderDataType::Vec2 }
        };

        m_VB->SetLoadout(Loadout);

        m_QuadStorage->m_VA->AddVertexBuffer(m_VB);
        m_QuadStorage->m_VA->AddIndexBuffer(m_IB);

        m_QuadStorage->m_Shader->Bind();
        m_QuadStorage->m_Shader->SetUniformInt("u_Texture", 0);

        m_QuadStorage->m_DefaultTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        m_QuadStorage->m_DefaultTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    }

    void Renderer2D::Shutdown()
    {
        delete m_QuadStorage;
    }


    void Renderer2D::StartScene(const OrthoCamera& camera)
    {
        m_QuadStorage->m_Shader->Bind();
        m_QuadStorage->m_Shader->SetUniformMat4("u_PVMat", camera.GetProjectionViewMat());
    }

    void Renderer2D::StopScene()
    {
        
    }


    // for normal quads (the ones that dont rotate) //
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color, int zIndex)
    {
        Renderer2D::DrawQuad({ position.x, position.y, zIndex * 0.1 }, scale, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
    {
        // this will take one extra draw call to bind if we already bound it in the StartScene function.
        // we will later check for cache memory to see if we need to bind the shader and vertex array.
        m_QuadStorage->m_Shader->Bind();
        m_QuadStorage->m_VA->Bind();
        m_QuadStorage->m_DefaultTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

        m_QuadStorage->m_Shader->SetUniformVec4("u_Color", color);
        m_QuadStorage->m_Shader->SetUniformMat4("u_ModelMat", transform);
        m_QuadStorage->m_Shader->SetUniformFloat("u_TextureScale", 1.0f);

        RenderCommand::DrawThis(m_QuadStorage->m_VA);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const Ref<Texture2D>& texture, const glm::vec4& tint, int zIndex)
    {
        Renderer2D::DrawQuad({ position.x, position.y, zIndex}, scale, texture, tint);
    }
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture2D>& texture, const glm::vec4& tint)
    {
        m_QuadStorage->m_Shader->Bind();
        m_QuadStorage->m_VA->Bind();
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

        m_QuadStorage->m_Shader->SetUniformMat4("u_ModelMat", transform);
        m_QuadStorage->m_Shader->SetUniformVec4("u_Color", tint);
        m_QuadStorage->m_Shader->SetUniformFloat("u_TextureScale", texture->GetTextureScale());

        RenderCommand::DrawThis(m_QuadStorage->m_VA);
    }


    // for rotated quads //
    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float& rotation, const glm::vec2& scale, const glm::vec4& color, int zIndex)
    {
        Renderer2D::DrawRotatedQuad({ position.x, position.y, zIndex * 0.1 }, rotation, scale, color);
    }
    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& scale, const glm::vec4& color)
    {
        // this will take one extra draw call to bind if we already bound it in the StartScene function.
        // we will later check for cache memory to see if we need to bind the shader and vertex array.
        m_QuadStorage->m_Shader->Bind();
        m_QuadStorage->m_VA->Bind();
        m_QuadStorage->m_DefaultTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

        m_QuadStorage->m_Shader->SetUniformVec4("u_Color", color);
        m_QuadStorage->m_Shader->SetUniformMat4("u_ModelMat", transform);
        m_QuadStorage->m_Shader->SetUniformFloat("u_TextureScale", 1.0f);

        RenderCommand::DrawThis(m_QuadStorage->m_VA);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float& rotation, const glm::vec2& scale, const Ref<Texture2D>& texture, const glm::vec4& tint, int zIndex)
    {
        Renderer2D::DrawRotatedQuad({ position.x, position.y, zIndex}, rotation, scale, texture, tint);
    }
    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& scale, const Ref<Texture2D>& texture, const glm::vec4& tint)
    {
        m_QuadStorage->m_Shader->Bind();
        m_QuadStorage->m_VA->Bind();
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

        m_QuadStorage->m_Shader->SetUniformMat4("u_ModelMat", transform);
        m_QuadStorage->m_Shader->SetUniformVec4("u_Color", tint);
        m_QuadStorage->m_Shader->SetUniformFloat("u_TextureScale", texture->GetTextureScale());

        RenderCommand::DrawThis(m_QuadStorage->m_VA);
    }
}