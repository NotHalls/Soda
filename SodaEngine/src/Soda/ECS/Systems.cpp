#include "Systems.h"

#include "Soda/Renderer/Render.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"

#include "Soda/Renderer/Renderer2D.h"

#include "Soda/ECS/Components.h"
#include "Soda/ECS/Object.h"
#include "glm/trigonometric.hpp"


namespace Soda
{
    void Systems::OnUpdate(Timestep dt)
    {
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
        for(auto entity : group)
        {
            const auto& [Transform, Sprite] = group.get<TransformComponent, SpriteComponent>(entity);

            Renderer2D::DrawQuad(Transform.Transform, Sprite.Texture, Sprite.Color, Sprite.TextureScale);
            glm::mat4 transPos = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
            Renderer2D::DrawQuad(Transform.Transform + transPos, Sprite.Texture, Sprite.Color, Sprite.TextureScale);
        }
    }


    Object Systems::CreateObject(const std::string& name)
    {
        Object obj = { m_Registry.create(), this };
        obj.AddComponent<TransformComponent>(glm::mat4(1.0f));
        obj.AddComponent<NameComponent>(name);

        return obj;
    }
}