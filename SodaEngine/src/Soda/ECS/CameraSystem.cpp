#include "SD_PCH.h"

#include "Soda/Tools/Logger.h"
#include "glm/gtc/matrix_transform.hpp"

#include "CameraSystem.h"


namespace Soda
{
    void CameraSystem::SetOrthoCamera(float size, float nearPlane, float farPlane)
    {
        m_CameraSize = size;
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;

        RecalculateMatrix();
    }

    void CameraSystem::SetViewport(uint32_t width, uint32_t height)
    {
        m_AspectRatio = (float)width / (float)height;

        RecalculateMatrix();
    }


    void CameraSystem::RecalculateMatrix()
    {
        float leftSide = -m_CameraSize * m_AspectRatio * 0.5f;
        float rightSize = m_CameraSize * m_AspectRatio * 0.5f;
        float upSide = m_CameraSize * 0.5f;
        float bottomSide = -m_CameraSize * 0.5f;

        m_Projection = glm::ortho(leftSide, rightSize, bottomSide, upSide, m_NearPlane, m_FarPlane);
    }
}