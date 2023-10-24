#pragma once

#include "Soda/Renderer/RenderAPI.h"


namespace Soda
{
	class OpenGLRenderer : public RenderAPI
	{
		virtual void Init() override;

		virtual void ClearScreen(const glm::vec4& color = { 1.0f, 0.0f, 0.8f, 1.0f }) override;

		virtual void DrawThis(const std::shared_ptr<VertexArray>& VA) override;
	};
}