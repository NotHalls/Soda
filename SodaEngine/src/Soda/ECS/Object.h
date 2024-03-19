#pragma once

#include "Soda/_Main/Core.h"
#include "Systems.h"
#include <utility>


// the reason why its called an Object is because
// i like to call it as an Object and not an Entity
namespace Soda
{
    class Object
    {
    public:
        Object() = default;
        Object(const Object& object) = default;
        Object(entt::entity object, Systems* system)
            : m_Object(object), m_System(system)
        {}

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        { 
            SD_ENGINE_ASSERT(!HasComponent<T>(), "The Component Already Exists")
            return m_System->m_Registry.emplace<T>(m_Object, std::forward<Args>(args)...);
        }

        template<typename T>
        T& DeleteComponent()
        {
            SD_ENGINE_ASSERT(HasComponent<T>(), "The Component Doesnt Exist")
            m_System->m_Registry.remove<T>(m_Object);
        }
        

        template<typename T>
        T& GetComponent()
        {
            SD_ENGINE_ASSERT(HasComponent<T>(), "The Component Doesnt Exist")
            return m_System->m_Registry.get<T>(m_Object);
        }
        
        template<typename T>
        bool HasComponent()
        { return m_System->m_Registry.all_of<T>(m_Object); }
        
    public:
        operator bool() const
        { return m_Object != entt::null; }

    private:
        Systems* m_System = nullptr;

        entt::entity m_Object = entt::null;
    };
}