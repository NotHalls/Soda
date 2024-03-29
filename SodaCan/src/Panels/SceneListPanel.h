#pragma once

#include "Soda.h"
#include "Soda/ECS/Components.h"
#include "Soda/ECS/Object.h"
#include <string>



namespace Soda
{
    class SceneListPanel
    {
    public:
        SceneListPanel() = default;
        SceneListPanel(const Ref<Systems>& system)
        { SetSystem(system); }

        void SetSystem(const Ref<Systems>& system);

        void OnImGuiRender();

    private:
        void DrawListObject(Object obj, const std::string& name);
    private:
        Ref<Systems> m_CurrentSystem;
        Object m_SelectedObj;
    };
}