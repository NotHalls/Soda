#include "SD_PCH.h"

#include "Render.h"


namespace Soda
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData;

	void Renderer::StartScene(OrthoCamera& camera)
	{
		m_SceneData->ProjectionViewMat = camera.GetProjectionViewMat();
	}

	void Renderer::StopScene()
	{}


	void Renderer::PushThis(const std::shared_ptr<VertexArray>& VA, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		VA->Bind();

		shader->SetUniformMat4("u_PVMat", m_SceneData->ProjectionViewMat);
		shader->SetUniformMat4("u_ModelMat", transform);

		RenderCommand::DrawThis(VA);
	}
}