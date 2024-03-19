#pragma once

#include "Soda/ECS/Components.h"
#include "glm/glm.hpp"


namespace Soda
{
    // Global Components
    struct TagComponent
    {
        std::string Tag = "Object";

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            : Tag(tag)
        {}
    };

    struct TransformComponent
    {
        glm::mat4 Transform{1.0f};

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(glm::mat4 transform)
            : Transform(transform)
        {}
    };


    // 2D Components
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