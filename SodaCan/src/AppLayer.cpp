#include "AppLayer.h"

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

        FramebufferInfo m_FramebufferInfo;
        m_FramebufferInfo.width = 1280;
        m_FramebufferInfo.height = 720;
        m_Framebuffer = Framebuffer::Create(m_FramebufferInfo);
    }

    void SodaCan::OnUpdate(Timestep dt)
    {
        SD_PROFILE();

        m_Framebuffer->Bind();

        {
            SD_PROFILE_SCOPE("Camera Update")
            m_CameraController.OnUpdate(dt);
        }

        {
            SD_PROFILE_SCOPE("Screen Settings")
            RenderCommand::ClearScreen({ 0.1f, 0.1f, 0.1f, 1.0f });
            Renderer2D::ResetRendererStats();
        }
            
        {
            SD_PROFILE_SCOPE("Update Functions")

            Renderer2D::StartScene(m_CameraController.GetCamera());
            {
                Renderer2D::DrawQuad({0.0f, 0.0f, -0.6f}, {10.0f, 10.0f}, m_BoxTexture);

                Renderer2D::DrawQuad({1.0f, 2.0f, 0.1f}, {1.0f, 1.0f}, glm::vec4(1.0f));

                Renderer2D::DrawRotatedQuad(m_BoxPosition, m_BoxRotation, m_BoxScale, m_BoxColor);
            }


            // THE STRESSSS TESTTT //
            for(float x = -5.0f; x <= 5.0f; x += m_MulFactor)
            {
                for(float y = -5.0f; y <= 5.0f; y += m_MulFactor)
                {
                    glm::vec4 gradColor = {(y + m_GradFactor) / (5.0f + m_GradFactor), (x + m_GradFactor) / (5.0f + m_GradFactor), 0.5f, 0.9f};
                    Renderer2D::DrawQuad({x, y, -0.5f}, glm::vec2(0.45f), gradColor);
                }
            }
            Renderer2D::StopScene();

            m_Framebuffer->Unbind();
        }
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

            ImGui::Begin("Stats");
            {
                ImGui::Text("");
                ImGui::DragFloat3("Box Position", &m_BoxPosition.x, 0.1f);
                ImGui::DragFloat("Box Rotation", &m_BoxRotation, 0.1f);
                ImGui::DragFloat2("Box Scale", &m_BoxScale.x, 0.1f);
                ImGui::ColorEdit4("Box Color", &m_BoxColor.x);
                ImGui::Text("");
                ImGui::DragFloat("Grad Factor", &m_GradFactor, 0.1f);
                ImGui::DragFloat("Multiply Factor", &m_MulFactor, 0.1f);

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
            }
            ImGui::End();


            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Scene");
            {
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