#include "SodaCan2D.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Soda/Renderer/OpenGL/OpenGLShader.h"


SodaCan2D::SodaCan2D()
    : Layer("SodaCan2D"), m_CameraController(1280.0f / 720.0f, true)
{}

void SodaCan2D::OnAttach()
{
    m_BoxTexture = Soda::Texture2D::Create("assets/textures/GingerCat.png");

    m_BoxVA.reset(Soda::VertexArray::Create());

    float boxVertices[]
    {
        -0.5f,  0.5f, 0.0f,		0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,		1.0f, 1.0f,	
         0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,		0.0f, 0.0f
    };

    int boxIndices[]
    {
        0, 1, 2, 0, 2, 3
    };

    std::shared_ptr<Soda::VertexBuffer> m_BoxVB;
    m_BoxVB.reset(Soda::VertexBuffer::Create(boxVertices, sizeof(boxVertices)));
    m_BoxVB->Bind();
    std::shared_ptr<Soda::IndexBuffer> m_BoxIB;
    m_BoxIB.reset(Soda::IndexBuffer::Create(boxIndices, 24));
    m_BoxIB->Bind();

    Soda::BufferLoadout boxLoadout = {
        { "a_position", Soda::ShaderDataType::Vec3 },
        { "a_texCoords", Soda::ShaderDataType::Vec2 }
    };

    m_BoxVB->SetLoadout(boxLoadout);

    m_BoxVA->AddVertexBuffer(m_BoxVB);
    m_BoxVA->AddIndexBuffer(m_BoxIB);

    m_Shader2D.reset(Soda::Shader::Create("assets/shaders/Shader2D.glsl"));
}

void SodaCan2D::OnUpdate(Soda::Timestep dt)
{
    m_CameraController.OnUpdate(dt);

    m_BoxTransform = glm::translate(glm::mat4(1.0f), m_BoxPosition) *
                     glm::rotate(glm::mat4(1.0f), m_BoxRotation, { 0.0f, 0.0f, 1.0f }) *
                     glm::scale(glm::mat4(1.0f), m_BoxScale);

    Soda::Renderer::StartScene(m_CameraController.GetCamera());
    {
        Soda::RenderCommand::ClearScreen({ 0.1f, 0.1f, 0.1f, 1.0f });

        std::dynamic_pointer_cast<Soda::OpenGLShader>(m_Shader2D)->SetUniformVec4("u_Color", m_BoxColor);
        Soda::Renderer::PushThis(m_BoxVA, m_Shader2D, m_BoxTransform);
    }
    Soda::Renderer::StopScene();
}


void SodaCan2D::OnEvent(Soda::Event& event)
{
    m_CameraController.OnEvent(event);
}

void SodaCan2D::OnImGuiUpdate()
{
    ImGui::Begin("Stats");
    {
        ImGui::DragFloat2("Box Position", &m_BoxPosition.x, 0.1f);
        ImGui::DragFloat("Box Rotation", &m_BoxRotation, 0.1f);
        ImGui::DragFloat2("Box Scale", &m_BoxScale.x, 0.1f);
        ImGui::ColorEdit4("Box Color", &m_BoxColor.x);
    }
    ImGui::End();
}

void SodaCan2D::OnDetach()
{}