#include "SD_PCH.h"

#include "Render.h"

#include "Soda/Renderer/OpenGL/OpenGLShader.h"


namespace Soda
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData;


	void Renderer::Init(unsigned int width, unsigned int height)
	{
		RenderCommand::Init(width, height);
	}

	void Renderer::StartScene(OrthoCamera& camera)
	{
		m_SceneData->ProjectionViewMat = camera.GetProjectionViewMat();
	}
	void Renderer::StartScene(PerspectiveCamera& camera)
	{
		m_SceneData->ProjectionViewMat = camera.GetProjectionViewMat();
		m_SceneData->CameraPosition = camera.GetPosition();
	}

	void Renderer::StopScene()
	{}

	void Renderer::OnWindowResize(unsigned int width, unsigned int height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}


	void Renderer::PushThis(const std::shared_ptr<VertexArray>& VA, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		VA->Bind();

		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_PVMat", m_SceneData->ProjectionViewMat);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ModelMat", transform);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformVec3("u_ViewPos", m_SceneData->CameraPosition);

		RenderCommand::DrawThis(VA);
	}
}