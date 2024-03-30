#include "SceneListPanel.h"

#include "Soda/ECS/Components.h"
#include "imgui.h"


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
            if(ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)obj, ImGuiTreeNodeFlags_DefaultOpen, obj.GetComponent<NameComponent>().Name.c_str()))
            {
                auto& transform = obj.GetComponent<TransformComponent>().Transform;
                ImGui::DragFloat3("Position", glm::value_ptr(transform[3]));

                ImGui::TreePop();
            }
        }
    }
}