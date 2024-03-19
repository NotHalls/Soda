#pragma once

#include "Systems.h"



namespace Soda
{
    class Object
    {
    public:
        Object() = default;
        Object(entt::entity object, Systems* system);
        
    private:
        Systems* m_System = nullptr;

        entt::entity m_Object{0};
    };
}