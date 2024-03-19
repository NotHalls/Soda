#pragma once

#include "entt.hpp"
#include "glm/glm.hpp"

#include "Soda/_Main/Timestep.h"


namespace Soda
{
    class Object;

    class Systems
    {
    public:
        Systems() = default;
        ~Systems() = default;

        Object CreateObject(); // Object is basicly entity. I just like to call it Object and not Entity
        
        // entity functions
        void OnUpdate(Timestep dt);

    private:
        entt::registry m_Registry;

        friend class Object;
    };
}