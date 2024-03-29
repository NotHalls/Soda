#include "SceneListPanel.h"

#include "imgui.h"


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
            m_CurrentSystem->m_Registry.view<NameComponent>().each([&](auto obj, auto& nameComponent)
            {
                Object list(obj, m_CurrentSystem.get());
                ImGui::Text("%s", nameComponent.Name.c_str());
            });
        }
        ImGui::End();
    }
}