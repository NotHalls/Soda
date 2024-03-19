#include "Systems.h"

#include "Soda/Renderer/Renderer2D.h"
#include "glm/glm.hpp"

#include "Soda/ECS/Components.h"


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
}