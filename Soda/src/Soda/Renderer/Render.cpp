#include "SD_PCH.h"

#include "Render.h"


namespace Soda
{
	void Renderer::StartRenderer()
	{}

	void Renderer::StopRenderer()
	{}


	void Renderer::PushThis(const std::shared_ptr<VertexArray>& VA)
	{
		VA->Bind();
		RenderCommand::DrawThis(VA);
	}
}