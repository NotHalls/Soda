#include "SodaCan2D.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


SodaCan2D::SodaCan2D()
    : Layer("SodaCan2D"), m_CameraController(1280.0f / 720.0f, true)
{}

void SodaCan2D::OnAttach()
{
    m_BoxTexture = Soda::Texture2D::Create("assets/textures/Grid.png");
}

void SodaCan2D::OnUpdate(Soda::Timestep dt)
{

    {
        m_CameraController.OnUpdate(dt);
    }

    {
        Soda::RenderCommand::ClearScreen({ 0.1f, 0.1f, 0.1f, 1.0f });
    }
    
    {
        Soda::Renderer2D::StartScene(m_CameraController.GetCamera());
        {
            Soda::Renderer2D::DrawQuad(m_BoxPosition, m_BoxRotation, m_BoxScale, m_BoxColor);
            Soda::Renderer2D::DrawQuad({ 10.0f, 0.0f}, 0.0f, { 1.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f }, 2);

            Soda::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, 0.0f, { 5.0f, 5.0f }, m_BoxTexture);
        }
        Soda::Renderer2D::StopScene();
    }
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