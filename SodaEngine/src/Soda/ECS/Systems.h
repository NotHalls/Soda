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

        // Object specific code
        Object CreateObject(const std::string& name = "Object"); // Object is basicly entity. I just like to call it Object and not Entity
        void DestroyObject(Object obj);
        
        // entity functions
        void OnUpdate(Timestep dt);
        void OnResize(uint32_t width, uint32_t height);

    private:
        entt::registry m_Registry;

        friend class Object;
        friend class Panels;
    };
}