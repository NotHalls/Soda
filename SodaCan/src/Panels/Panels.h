#pragma once

#include "Soda.h"

#include "SceneListPanel.h"


namespace Soda
{
    class Panels
    {
    public:
        Panels() = default;

        void SetSystem(const Ref<Systems>& system);
        void OnImGuiRender();

    private:
        Ref<Systems> m_CurrentSystem;
        SceneListPanel m_SceneListsPanel;
    };
}