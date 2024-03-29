#include "SceneListPanel.h"

#include "Soda/ECS/Components.h"
#include "Soda/ECS/Object.h"
#include "imgui.h"
#include <cstdint>
#include <string>


namespace Soda
{
    void SceneListPanel::SetSystem(const Ref<Systems>& system)
    {
        m_CurrentSystem = system;
    }

    void SceneListPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene List");
        {
            // now because we need to mention nameComponent in the lambda
            // i decided to pass in the std::string Name of the object too instead of making a new var in the DrawListObject() function
            m_CurrentSystem->m_Registry.view<NameComponent>().each([&](auto obj, auto& nameComponent)
            {
                Object list(obj, m_CurrentSystem.get());
                DrawListObject(list, nameComponent.Name); // dont really know if i should do this or just pass in the object
            });
        }
        ImGui::End();
    }


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
}