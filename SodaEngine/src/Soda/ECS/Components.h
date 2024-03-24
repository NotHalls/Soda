#pragma once

#include "Soda/ECS/Components.h"
#include "Soda/Renderer/Texture.h"
#include "Soda/Tools/SpriteSheet.h"
#include "glm/glm.hpp"
#include <string>


namespace Soda
{
    // Global Components
    struct NameComponent
    {
        std::string Name = "Object";

        NameComponent() = default;
        NameComponent(const NameComponent&) = default;
        NameComponent(const std::string& name)
            : Name(name)
        {}
    };

    struct TagComponent
    {
        std::string Tag = "NULL";

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
        TransformComponent(const glm::mat4& transform)
            : Transform(transform)
        {}
    };


    // 2D Components
    struct SpriteComponent
    {
        glm::vec4 Color{1.0f, 1.0f, 1.0f, 1.0f};
        Ref<Texture2D> Texture = nullptr;
        Ref<SpriteSheetTexture> SpriteSheetTexture = nullptr;
        float TextureScale = 1.0f;

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(const glm::vec4& color, const Ref<Texture2D>& texture = nullptr)
            : Color(color), Texture(texture)
        {}
    };
}