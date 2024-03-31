#include "SceneListPanel.h"

#include "Soda/ECS/CameraSystem.h"
#include "Soda/ECS/Components.h"
#include "glm/trigonometric.hpp"
#include "imgui.h"
#include <cstdint>


namespace Soda
{
    void SceneListPanel::DrawListObject(Object obj, const std::string& name)
    {
        ImGuiTreeNodeFlags flags = ((m_SelectedObj == obj) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)obj, flags, name.c_str());
        if(ImGui::IsItemClicked())
        {
            m_SelectedObj = obj;
        }


        if(opened)
        {
            ImGui::TreePop();
        }
    }


    void SceneListPanel::DrawObjectProperties(Object obj)
    {
        if(obj.HasComponent<NameComponent>())
        {
            auto& name = obj.GetComponent<NameComponent>().Name;

            char buffer[512];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), name.c_str());

            if(ImGui::InputText("Name", buffer, sizeof(buffer)))
                name = std::string(buffer);

            ImGui::Spacing();
        }


        if(obj.HasComponent<TransformComponent>())
        {        
            if(ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                auto& transform = obj.GetComponent<TransformComponent>().Transform;
                ImGui::DragFloat3("Position", glm::value_ptr(transform[3]));

                ImGui::TreePop();
            }
        }


        if(obj.HasComponent<CameraComponent>())
        {        
            if(ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
            {
                auto& camera = obj.GetComponent<CameraComponent>();

                ImGui::Checkbox("Primary", &camera.PrimaryCamera);
                ImGui::Checkbox("Fixed Aspect Ratio", &camera.FixedAspectRatio);

                const char* cameraTypes[] = {"Orthographic", "Perspective"};
                const char* cameraTypeToString = cameraTypes[(int)camera.Camera.GetCameraType()];

                if(ImGui::BeginCombo("Type", cameraTypeToString))
                {
                    for(int i = 0; i < 2; i++)
                    {
                        if(ImGui::Selectable(cameraTypes[i]))
                        {
                            cameraTypeToString = cameraTypes[i];
                            camera.Camera.SetCameraType((CameraSystem::CameraType)i);
                        }
                    }

                    ImGui::EndCombo();
                }

                if(camera.Camera.GetCameraType() == CameraSystem::CameraType::Orthographic)
                {
                    float orthoCamSize = camera.Camera.GetOrthoCameraSize();
                    if(ImGui::DragFloat("View Size", &orthoCamSize))
                        camera.Camera.SetOrthoCameraSize(orthoCamSize);

                    float orthoNearPlane = camera.Camera.GetOrthoNearPlane();
                    if(ImGui::DragFloat("Near Plane", &orthoNearPlane))
                        camera.Camera.SetOrthoNearPlane(orthoNearPlane);

                    float orthoFarPlane = camera.Camera.GetOrthoFarPlane();
                    if(ImGui::DragFloat("Far Plane", &orthoFarPlane))
                        camera.Camera.SetOrthoFarPlane(orthoFarPlane);
                }
                else
                {
                    float perspFov = glm::degrees(camera.Camera.GetPerspectiveFov());
                    if(ImGui::DragFloat("Fov", &perspFov))
                        camera.Camera.SetPerspectiveFov(perspFov);

                    float perspNearPlane = camera.Camera.GetPerspectiveNearPlane();
                    if(ImGui::DragFloat("Near Plane", &perspNearPlane))
                        camera.Camera.SetPerspectiveNearPlane(perspNearPlane);

                    float perspFarPlane = camera.Camera.GetPerspectiveFarPlane();
                    if(ImGui::DragFloat("Far Plane", &perspFarPlane))
                        camera.Camera.SetPerspectiveFarPlane(perspFarPlane);
                }

                ImGui::TreePop();
            }
        }
    }
}