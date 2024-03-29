#pragma once

#include "Soda/Renderer/CameraComponent.h"


namespace Soda
{
    class CameraSystem : public TheCamera
    {
    public:
        CameraSystem()
        {  }
        virtual ~CameraSystem() = default;

        void SetOrthoCamera(float size, float nearPlane, float farPlane);

        void SetViewport(uint32_t width, uint32_t height);

        const float GetCameraSize() const
        { return m_CameraSize; }
        void SetCameraSize(float size)
        { m_CameraSize = size; RecalculateMatrix(); }
        
    private:
        void RecalculateMatrix();
    private:
        float m_AspectRatio = 0.0f;

        float m_CameraSize = 10.0f;
        float m_NearPlane = 1.0f, m_FarPlane = -1.0f;
    };
}