#pragma once

#include "glm/glm.hpp"


namespace Soda
{
    struct TransformComponent
    {
        glm::mat4 Transform{1.0f};

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(glm::mat4 transform)
            : Transform(transform)
        {}
    };

    struct SpriteComponent
    {
        glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(glm::vec4 color)
            : Color(color)
        {}
    };
}