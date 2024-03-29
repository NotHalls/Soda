#pragma once

#include "Soda/ECS/CameraSystem.h"
#include "Soda/ECS/ScriptEntity.h"

#include "Soda/Renderer/Texture.h"
#include "Soda/Tools/SpriteSheet.h"

#include "Soda/Renderer/CameraComponent.h"
#include <functional>


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

    struct LableComponent
    {
        std::string Lable = "NULL";

        LableComponent() = default;
        LableComponent(const LableComponent&) = default;
        LableComponent(const std::string& lable)
            : Lable(lable)
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


    // Other Components
    struct CameraComponent
    {
        CameraSystem Camera;
        bool PrimaryCamera = true;
        bool FixedAspectRatio = false;

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
    };

    struct ScriptComponent
    {
        ScriptEntity* Script = nullptr;

        ScriptEntity*(*InitScript)();
        void (*DestroyScript)(ScriptComponent*);

        template<typename T>
        void Bind()
        {
            InitScript = []()
            { return static_cast<ScriptEntity*>(new T()); };

            DestroyScript = [](ScriptComponent* script)
            {
                delete script->Script;
                script->Script = nullptr;
            };
        }
    };
}