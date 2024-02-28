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

    Soda::FramebufferInfo m_FramebufferInfo;
    m_FramebufferInfo.width = 1280;
    m_FramebufferInfo.height = 720;
    m_Framebuffer = Soda::Framebuffer::Create(m_FramebufferInfo);
}

void SodaCan2D::OnUpdate(Soda::Timestep dt)
{
    m_Framebuffer->Bind();

    {
        m_CameraController.OnUpdate(dt);
    }

    {
        Soda::RenderCommand::ClearScreen({ 0.1f, 0.1f, 0.1f, 1.0f });
    }
    
    {
        Soda::Renderer2D::StartScene(m_CameraController.GetCamera());
        {
            Soda::Renderer2D::DrawQuad(m_BoxPosition, m_BoxScale, m_BoxColor);
            Soda::Renderer2D::DrawRotatedQuad({2.0f, 0.0f}, glm::radians(45.0f), { 1.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f }, 2);

            Soda::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.9f }, { 5.0f, 5.0f }, m_BoxTexture);
        }
        Soda::Renderer2D::StopScene();
    }

    m_Framebuffer->Unbind();
}


void SodaCan2D::OnEvent(Soda::Event& event)
{
    m_CameraController.OnEvent(event);
}

void SodaCan2D::OnImGuiUpdate()
{
    static bool dockspaceEnabl = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceEnabl, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Close"))
                Soda::App::Get().CloseApp();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();

        ImGui::Begin("Stats");
        {
            ImGui::DragFloat2("Box Position", &m_BoxPosition.x, 0.1f);
            ImGui::DragFloat("Box Rotation", &m_BoxRotation, 0.1f);
            ImGui::DragFloat2("Box Scale", &m_BoxScale.x, 0.1f);
            ImGui::ColorEdit4("Box Color", &m_BoxColor.x);
        }
        ImGui::End();

        ImGui::Begin("Scene");
        {
            ImGui::Image((void*)m_Framebuffer->GetFrameTextureID(), ImVec2(1280.0f, 720.0f));
        }
        ImGui::End();

    }

    ImGui::End();
}

void SodaCan2D::OnDetach()
{}