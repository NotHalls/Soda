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

        void DrawListObject(Object obj, const std::string& name);
        
    private:
        Ref<Systems> m_CurrentSystem;
        Object m_SelectedObj;
    };
}