#pragma once


#include "RenderAPI.h"


namespace Soda
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{ m_renderAPI->Init(); }

		inline static void ClearScreen(const glm::vec4& color = { 1.0f, 0.0f, 0.8f, 1.0f })
		{ m_renderAPI->ClearScreen(color); }

		inline static void DrawThis(const std::shared_ptr<VertexArray>& VA)
		{ m_renderAPI->DrawThis(VA); }

	private:
		static RenderAPI* m_renderAPI;
	};
}