#pragma once

#include "glm/glm.hpp"

#include "VertexArray.h"


namespace Soda
{
	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
	public:
		virtual void ClearScreen(const glm::vec4& color = {1.0f, 0.0f, 0.8f, 1.0f}) = 0;

		virtual void DrawThis(const std::shared_ptr<VertexArray>& VA) = 0;

		inline static API GetAPI()
		{ return m_API; }

	private:
		static API m_API;
	};
}