#include "Systems.h"

#include "glm/glm.hpp"

#include "Soda/Renderer/Renderer2D.h"

#include "Soda/ECS/Components.h"
#include "Soda/ECS/Object.h"


namespace Soda
{
    void Systems::OnUpdate(Timestep dt)
    {
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
        for(auto entity : group)
        {
            const auto& [Transform, Sprite] = group.get<TransformComponent, SpriteComponent>(entity);

            Renderer2D::DrawQuad(Transform.Transform, Sprite.Color);
        }
    }


    Object Systems::CreateObject()
    {
        Object obj = { m_Registry.create(), this };
        obj.AddComponent<TransformComponent>(glm::mat4(1.0f));
        obj.AddComponent<TagComponent>("NULL");

        return obj;
    }
}