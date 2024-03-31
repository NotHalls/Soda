#include "SD_PCH.h"

#include "Soda/Tools/Logger.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "CameraSystem.h"


namespace Soda
{
    void CameraSystem::SetOrthoCamera(float size, float nearPlane, float farPlane)
    {
        m_OrthoCamSize = size;
        m_OrthoNearPlane = nearPlane;
        m_OrthoFarPlane = farPlane;

        RecalculateMatrix();
    }
    void CameraSystem::SetPersCamera(float FOV, float nearPlane, float farPlane)
    {
        m_PerspectiveFOV = FOV;
        m_PersNearPlane = nearPlane;
        m_PersFarPlane = farPlane;

        RecalculateMatrix();
    }

    void CameraSystem::SetViewport(uint32_t width, uint32_t height)
    {
        m_AspectRatio = (float)width / (float)height;
        RecalculateMatrix();
    }


    void CameraSystem::RecalculateMatrix()
    {
        if(m_CameraType == CameraType::Orthographic)
        {
            float leftSide = -m_OrthoCamSize * m_AspectRatio * 0.5f;
            float rightSize = m_OrthoCamSize * m_AspectRatio * 0.5f;
            float upSide = m_OrthoCamSize * 0.5f;
            float bottomSide = -m_OrthoCamSize * 0.5f;

            m_Projection = glm::ortho(leftSide, rightSize, bottomSide, upSide, m_OrthoNearPlane, m_OrthoFarPlane);
        }
        else
        {
            m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PersNearPlane, m_PersFarPlane);
        }
    }
}