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

        // These command handle the batch rendering stuff and default shader uniform stuff
        static void StartScene(const OrthoCamera& camera);
        static void StopScene();

        // this is the draw call we make
        static void DrawBatch();

        // normal quads that dont rotate
        static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture2D>& texture);


        // rotation takes aq lot of shit to calculate, so we are making seperate function for rotated quads
        static void DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& scale, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const float& rotation, const glm::vec2& scale, const Ref<Texture2D>& texture);
    };
}

// when you make a Renderer3D, dont forget about
// std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformVec3("u_ViewPos", m_SceneData->CameraPosition); // i forgot what this was about