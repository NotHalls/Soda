#pragma once

#include "RenderCommand.h"


namespace Soda
{
	class Renderer
	{
	public:
		static void	StartRenderer();
		static void StopRenderer();

		static void PushThis(const std::shared_ptr<VertexArray>& VA);


		static RenderAPI::API GetAPI()
		{ return RenderAPI::GetAPI(); }
	};
}