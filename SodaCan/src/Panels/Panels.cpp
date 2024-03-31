#include "Panels.h"

#include "imgui.h"


namespace Soda
{
    void Panels::SetSystem(const Ref<Systems>& system)
    {
        m_CurrentSystem = system;
    }

    void Panels::OnImGuiRender()
    {
        ImGui::Begin("Scene List");
        {
            // now because we need to mention nameComponent in the lambda
            // i decided to pass in the std::string Name of the object too instead of making a new var in the DrawListObject() function
            m_CurrentSystem->m_Registry.view<NameComponent>().each([&](auto obj, auto& nameComponent)
            {
                Object list(obj, m_CurrentSystem.get());
                m_SceneListsPanel.DrawListObject(list, nameComponent.Name); // dont really know if i should do this or just pass in the object
            });

            if(ImGui::IsWindowHovered() && ImGui::IsMouseDown(0))
                m_SceneListsPanel.m_SelectedObj = {};
        }
        ImGui::End();

        ImGui::Begin("Details");
        {
            if(m_SceneListsPanel.m_SelectedObj)
            {
                m_SceneListsPanel.DrawObjectProperties(m_SceneListsPanel.m_SelectedObj);
            }
        }
        ImGui::End();
    }
}