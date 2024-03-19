#pragma once

#include "entt.hpp"
#include "glm/glm.hpp"

#include "Soda/_Main/Timestep.h"


namespace Soda
{
    class Systems
    {
    public:
        Systems() = default;
        ~Systems() = default;

        entt::entity CreateEntity()
        { return m_Registry.create(); }


        // @TEMP
        entt::registry& GetReg()
        { return m_Registry; }

        
        // entity functions
        void OnUpdate(Timestep dt);

    private:
        entt::registry m_Registry;
    };
}