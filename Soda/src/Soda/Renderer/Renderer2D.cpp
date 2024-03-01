#include "SD_PCH.h"

#include "Renderer2D.h"
#include "Soda/Renderer/Render.h"

#include "Soda/Renderer/VertexArray.h"
#include "Soda/Renderer/Shaderer.h"
#include "Soda/Renderer/Texture.h"


namespace Soda
{
    struct QuadVertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 tecCoords;
        // uint32_t texID;
    };

    struct QuadInfo
    {
        const uint32_t m_maxQuads = 10000;
        const uint32_t m_maxVertices = m_maxQuads * 4;
        const uint32_t m_maxIndices = m_maxQuads * 6;

        Ref<VertexArray> m_VA;
        Ref<VertexBuffer> m_VB;
        Ref<Shader> m_Shader;
        Ref<Texture2D> m_DefaultTexture;

        QuadVertex *m_QuadVertexStart = nullptr, *m_QuadVertexPtr = nullptr;
        uint32_t m_IndicesCount = 0;
    };

    static QuadInfo m_QuadInfo;


    void Renderer2D::Init()
    {
        m_QuadInfo.m_VA.reset(VertexArray::Create());
        
        // setting up the vertex buffer
        m_QuadInfo.m_VB = VertexBuffer::Create(m_QuadInfo.m_maxVertices * sizeof(QuadVertex));
        m_QuadInfo.m_VB->Bind();
        m_QuadInfo.m_VB->SetLoadout({
            { "a_position", ShaderDataType::Vec3 },
            { "a_color", ShaderDataType::Vec4 },
            { "a_texCoords", ShaderDataType::Vec2 }
        });
        m_QuadInfo.m_VA->AddVertexBuffer(m_QuadInfo.m_VB);

        m_QuadInfo.m_QuadVertexStart = new QuadVertex[m_QuadInfo.m_maxVertices];


        // setting up the indices
        uint32_t* boxIndices = new uint32_t[m_QuadInfo.m_maxIndices];
        uint32_t offset = 0;
        for(uint32_t i = 0; i < m_QuadInfo.m_maxIndices; i += 6)
        {
            boxIndices[i + 0] = offset + 0;
            boxIndices[i + 1] = offset + 1;
            boxIndices[i + 2] = offset + 2;

            boxIndices[i + 3] = offset + 2;
            boxIndices[i + 4] = offset + 3;
            boxIndices[i + 5] = offset + 0;

            offset += 4;
        }
        Ref<IndexBuffer> m_IB = IndexBuffer::Create(boxIndices, m_QuadInfo.m_maxIndices);
        m_IB->Bind();
        m_QuadInfo.m_VA->AddIndexBuffer(m_IB);
        delete[] boxIndices;


        // other stuff
        m_QuadInfo.m_Shader.reset(Shader::Create("assets/shaders/Shader2D.glsl"));
        m_QuadInfo.m_Shader->Bind();
        m_QuadInfo.m_Shader->SetUniformInt("u_Texture", 0);

        m_QuadInfo.m_DefaultTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        m_QuadInfo.m_DefaultTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    }

    void Renderer2D::Shutdown()
    { }

    void Renderer2D::StartScene(const OrthoCamera& camera)
    {
        m_QuadInfo.m_Shader->Bind();
        m_QuadInfo.m_Shader->SetUniformMat4("u_PVMat", camera.GetProjectionViewMat());

        m_QuadInfo.m_QuadVertexPtr = m_QuadInfo.m_QuadVertexStart;

        m_QuadInfo.m_IndicesCount = 0;
    }

    void Renderer2D::StopScene()
    {
        // track all the vertices and send it to the gpu then do the draw call
        uint32_t dataSize = (uint8_t*)m_QuadInfo.m_QuadVertexPtr - (uint8_t*)m_QuadInfo.m_QuadVertexStart;
        m_QuadInfo.m_VB->SetData(m_QuadInfo.m_QuadVertexStart, dataSize);

        DrawBatch();
    }

    void Renderer2D::DrawBatch()
    {
            // this will take one extra draw call to bind if we already bound it in the StartScene function.
            // we will later check for cache memory to see if we need to bind the shader and vertex array.
    //         m_QuadInfo.m_Shader->Bind();
    //         m_QuadInfo.m_VA->Bind();
    //         m_QuadInfo.m_DefaultTexture->Bind();
    // 
    //         glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
    //                               glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
    // 
    //         m_QuadInfo.m_Shader->SetUniformVec4("u_Color", color);
    //         m_QuadInfo.m_Shader->SetUniformMat4("u_ModelMat", transform);
    //         m_QuadInfo.m_Shader->SetUniformFloat("u_TextureScale", 1.0f);
    
            RenderCommand::DrawThis(m_QuadInfo.m_VA, m_QuadInfo.m_IndicesCount);
    }


    // for normal quads (the ones that dont rotate)
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color, int zIndex)
    {
        Renderer2D::DrawQuad({ position.x, position.y, zIndex}, scale, color);
    }
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
    {
        // we pass through the mem block of each QuadVertex and set their attributes
        m_QuadInfo.m_QuadVertexPtr->position = {position};
        m_QuadInfo.m_QuadVertexPtr->color = color;
        m_QuadInfo.m_QuadVertexPtr->tecCoords = {0.0f, 0.0f};
        m_QuadInfo.m_QuadVertexPtr++;

        m_QuadInfo.m_QuadVertexPtr->position = {position.x + scale.x, position.y, position.z};
        m_QuadInfo.m_QuadVertexPtr->color = color;
        m_QuadInfo.m_QuadVertexPtr->tecCoords = {1.0f, 0.0f};
        m_QuadInfo.m_QuadVertexPtr++;

        m_QuadInfo.m_QuadVertexPtr->position = {position.x + scale.x, position.y + scale.y, position.z};
        m_QuadInfo.m_QuadVertexPtr->color = color;
        m_QuadInfo.m_QuadVertexPtr->tecCoords = {1.0f, 1.0f};
        m_QuadInfo.m_QuadVertexPtr++;

        m_QuadInfo.m_QuadVertexPtr->position = {position.x, position.y + scale.y, position.z};
        m_QuadInfo.m_QuadVertexPtr->color = color;
        m_QuadInfo.m_QuadVertexPtr->tecCoords = {0.0f, 1.0f};
        m_QuadInfo.m_QuadVertexPtr++;

        m_QuadInfo.m_IndicesCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const Ref<Texture2D>& texture, int zIndex)
    {
        Renderer2D::DrawQuad({ position.x, position.y, zIndex}, scale, texture);
    }
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture2D>& texture)
    {
        m_QuadInfo.m_Shader->Bind();
        m_QuadInfo.m_VA->Bind();
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

        m_QuadInfo.m_Shader->SetUniformMat4("u_ModelMat", transform);
        m_QuadInfo.m_Shader->SetUniformVec4("u_Color", texture->GetTextureTint());
        m_QuadInfo.m_Shader->SetUniformFloat("u_TextureScale", texture->GetTextureScale());

        RenderCommand::DrawThis(m_QuadInfo.m_VA);
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
        m_QuadInfo.m_Shader->Bind();
        m_QuadInfo.m_VA->Bind();
        m_QuadInfo.m_DefaultTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

        m_QuadInfo.m_Shader->SetUniformVec4("u_Color", color);
        m_QuadInfo.m_Shader->SetUniformMat4("u_ModelMat", transform);
        m_QuadInfo.m_Shader->SetUniformFloat("u_TextureScale", 1.0f);

        RenderCommand::DrawThis(m_QuadInfo.m_VA);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const float& rotation, const glm::vec2& scale, const Ref<Texture2D>& texture, int zIndex)
    {
        Renderer2D::DrawRotatedQuad({ position.x, position.y, zIndex}, rotation, scale, texture);
    }
    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& scale, const Ref<Texture2D>& texture)
    {
        m_QuadInfo.m_Shader->Bind();
        m_QuadInfo.m_VA->Bind();
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

        m_QuadInfo.m_Shader->SetUniformMat4("u_ModelMat", transform);
        m_QuadInfo.m_Shader->SetUniformVec4("u_Color", texture->GetTextureTint());
        m_QuadInfo.m_Shader->SetUniformFloat("u_TextureScale", texture->GetTextureScale());

        RenderCommand::DrawThis(m_QuadInfo.m_VA);
    }
}