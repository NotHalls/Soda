#include "SceneListPanel.h"

#include "Soda/ECS/Components.h"
#include "Soda/ECS/Object.h"
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
}