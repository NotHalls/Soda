#pragma once

#include "RenderCommand.h"

#include "Soda/Camera.h"
#include "Shaderer.h"

#include "glm/glm.hpp"


namespace Soda
{
	class Renderer
	{
	public:
		static void	StartScene(OrthoCamera& camera);
		static void StopScene();

		static void PushThis(const std::shared_ptr<VertexArray>& VA, const std::shared_ptr<Shader>& shader);


		static RenderAPI::API GetAPI()
		{ return RenderAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ProjectionViewMat;
		};

		static SceneData* m_SceneData;
	};
}