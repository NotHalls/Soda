#pragma once

#include "Soda/Renderer/Camera.h"
#include "Soda/Renderer/Texture.h"


namespace Soda
{
    // a super static class
    // super static means there will only be static functions and no member variables
    class Renderer2D
    {
    public:
        // Init and Shutdown are like the constructor and destructor of the class
        static void Init();
        static void Shutdown();

        // StartScene and StopScene are like the Begin and End of the class
        static void StartScene(const OrthoCamera& camera);
        static void StopScene();

        // DrawQuad takes a position, size, color, and either the zIndex or a vec3 position
        static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color, int zIndex = 0);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);

        // DrawQuad takes a position, size, texture, and either the zIndex or a vec3 position
        static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), int zIndex = 0);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));


        // rotation takes aq lot of shit to calculate, so we are making seperate function for rotated quads
        // DrawQuad takes a position, size, color, and either the zIndex or a vec3 position
        static void DrawRotatedQuad(const glm::vec2& position, const float& rotation, const glm::vec2& scale, const glm::vec4& color, int zIndex = 0);
        static void DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& scale, const glm::vec4& color);

        // DrawQuad takes a position, size, texture, and either the zIndex or a vec3 position
        static void DrawRotatedQuad(const glm::vec2& position, const float& rotation, const glm::vec2& scale, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), int zIndex = 0);
        static void DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& scale, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));
    };
}

// when you make a Renderer3D, dont forget about
// std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformVec3("u_ViewPos", m_SceneData->CameraPosition);