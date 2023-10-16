#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Soda
{
	class OrthoCamera
	{
	public:
		OrthoCamera(float left, float right, float down, float up)
			: m_projectionMat(glm::ortho(left, right, down, up, -1.0f, 1.0f)),
			  m_viewMat(1.0f),
			  m_viewProjectionMat(m_projectionMat * m_viewMat)
		{}

		void SetPosition(const glm::vec3& position)
		{ m_position = position; RecalculateMatrices(); }
		const glm::vec3& GetPosition() const
		{ return m_position; }

		void SetRotation(float rotation)
		{ m_rotation = rotation; RecalculateMatrices(); }
		float GetRotation() const
		{ return m_rotation; }
		 

		const glm::mat4& GetProjectionMat() const
		{ return m_projectionMat; }
		const glm::mat4& GetViewMat() const
		{ return m_viewMat; }
		const glm::mat4& GetProjectionViewMat() const
		{ return m_viewProjectionMat; }

	private:
		void RecalculateMatrices();
	private:
		glm::mat4 m_projectionMat;
		glm::mat4 m_viewMat;
		glm::mat4 m_viewProjectionMat;

		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;
	};
}