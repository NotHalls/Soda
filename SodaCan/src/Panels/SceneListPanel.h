#pragma once

#include "Soda.h"



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
        Ref<Systems> m_CurrentSystem;
    };
}