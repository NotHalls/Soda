#include "AppLayer.h"
#include "Soda/ECS/Components.h"
#include "Soda/ECS/Systems.h"
#include "Soda/Renderer/Renderer2D.h"
#include "Soda/Tools/SpriteSheet.h"
#include "Soda/_Main/App.h"
#include "Soda/_Main/Core.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>



namespace Soda
{
    SodaCan::SodaCan()
        : Layer("SodaCan"), m_CameraController(1280.0f / 720.0f, false)
    {}

    void SodaCan::OnAttach()
    {
        m_BoxTexture = Texture2D::Create(ASSETS_DIR "textures/Grid.png");
        m_TilesSpriteSheet = Texture2D::Create(ASSETS_DIR "game/spritesheets/spritesheet_tiles.png");

        m_IronTex = SpriteSheetTexture::TextureFromSheet(m_TilesSpriteSheet, {2, 9}, {128, 128});

        FramebufferInfo m_FramebufferInfo;
        m_FramebufferInfo.width = 1280;
        m_FramebufferInfo.height = 720;
        m_Framebuffer = Framebuffer::Create(m_FramebufferInfo);

        m_Scene = CreateRef<Systems>();

        m_Square = m_Scene->CreateObject();
        m_Square.AddComponent<SpriteComponent>(glm::vec4(0.5f, 1.0f, 1.0f, 1.0f));
        // m_Square.GetComponent<TagComponent>().Tag = "HI";
    }

    void SodaCan::OnUpdate(Timestep dt)
    {
        m_Framebuffer->Bind();

        // @TODO: The zoom still works when not focused
        if(m_IsPanelHovered)
            m_CameraController.OnUpdate(dt);

        RenderCommand::ClearScreen({ 0.1f, 0.1f, 0.1f, 1.0f });
        Renderer2D::ResetRendererStats();
            

        // Render Loop
        Renderer2D::StartScene(m_CameraController.GetCamera());
        {
            // m_Scene->OnUpdate(dt);
            Renderer2D::DrawQuad({0.0f, 0.0f, -0.9f}, {10.0f, 10.0f}, m_BoxTexture);
            Renderer2D::DrawQuad(m_BoxPosition, m_BoxScale, m_IronTex);
        }
        Renderer2D::StopScene();


        m_Framebuffer->Unbind();
    }


    void SodaCan::OnEvent(Event& event)
    {
        m_CameraController.OnEvent(event);
    }

    void SodaCan::OnImGuiUpdate()
    {
        static bool dockspaceEnable = true;
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
        ImGui::Begin("DockSpace Demo", &dockspaceEnable, window_flags);
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
                    App::Get().CloseApp();
                ImGui::EndMenu();
            }
            if(ImGui::BeginMenu("View"))
            {
                if(ImGui::MenuItem("Statistics"))
                    toggoleSetting(m_DefaultSettings, Settings::EnableRendererStats);
                if(ImGui::MenuItem("Profiler"))
                    toggoleSetting(m_DefaultSettings, Settings::ADD_SOMETHING_HERE);
                ImGui::EndMenu();
            }
        ImGui::EndMenuBar();

            if(m_Square)
            {
                ImGui::Begin("Properties");
                {
                    ImGui::Text("");
                    ImGui::Text("Object Tag: %s", m_Square.GetComponent<TagComponent>().Tag.c_str());
                    ImGui::DragFloat3("Box Position", &m_BoxPosition.x, 0.1f);
                    ImGui::DragFloat("Box Rotation", &m_BoxRotation, 0.1f);
                    ImGui::DragFloat2("Box Scale", &m_BoxScale.x, 0.1f);
                    ImGui::ColorEdit4("Box Color", glm::value_ptr(m_Square.GetComponent<SpriteComponent>().Color));
                    
                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();
                    
                    ImGui::DragFloat("Grad Factor", &m_GradFactor, 0.1f);
                    ImGui::DragFloat("Multiply Factor", &m_MulFactor, 0.1f);
                }
                ImGui::End();
            }

            if(m_DefaultSettings & Settings::EnableRendererStats)
            {
                ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
                ImGui::Begin("Renderer Stats", nullptr);
                {
                    ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
                    ImGui::Text("%.1f FPS",ImGui::GetIO().Framerate);
                    ImGui::Text("");
                    // renderer2D stats
                    Renderer2D::RendererStats stats = Renderer2D::GetRendererStats();

                    ImGui::Text("Draw Calls: %d", stats.noOfDrawCalls);
                    ImGui::Text("Textures: %d", stats.noIfTextures);
                    ImGui::Text("Quads: %d", stats.noOfQuads);
                    ImGui::Spacing();
                    ImGui::Text("Triangles: %d", stats.QueryNoOfTriangles());
                    ImGui::Text("Vertices: %d", stats.QueryNoOfVertices());
                    ImGui::Text("Indices: %d", stats.QueryNoOfIndices());
                }
                ImGui::End();   
                ImGui::PopStyleColor();
            }
            // if(m_DefaultSettings & Settings::)


            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Scene");
            {
                // Checks is the panel is Focused
                // @TODO: The Inputs should be consumed by the ImGui Panel and not the mani window.
                m_IsPanelFocused = ImGui::IsWindowFocused();
                m_IsPanelHovered = ImGui::IsWindowHovered();

                App::Get().GetImGuiLayer()->ShouldConsumeEvents(!m_IsPanelHovered);

                // put this inside a OnWindowResize Callback somehow
                // because we dont wanna check the scene/viewport each frame,
                // we only wanna do it when we resize.
                ImVec2 sceneSize = ImGui::GetContentRegionAvail();
                if(m_ViewportSize != *((glm::vec2*)&sceneSize))
                {
                    m_ViewportSize = {sceneSize.x, sceneSize.y};
                    m_Framebuffer->Redo(m_ViewportSize.x, m_ViewportSize.y);

                    m_CameraController.WhenResized(m_ViewportSize.x, m_ViewportSize.y);
                }
                // till here...
                ImGui::Image((void*)m_Framebuffer->GetFrameTextureID(), ImVec2(sceneSize.x, sceneSize.y), ImVec2(0, 1), ImVec2(1, 0));
            }
            ImGui::End();
            ImGui::PopStyleVar();

        }

        ImGui::End();
    }

    void SodaCan::OnDetach()
    {
        Renderer2D::Shutdown();
    }
}