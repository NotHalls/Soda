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
		static void Init(unsigned int width, unsigned int height);

		static void	StartScene(OrthoCamera& camera);
		static void StartScene(PerspectiveCamera& camera);
		static void StopScene();

		static void PushThis(const std::shared_ptr<VertexArray>& VA,
			const std::shared_ptr<Shader>& shader,
			const glm::mat4& transform = glm::mat4(1.0f));


		static RenderAPI::API GetAPI()
		{ return RenderAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ProjectionViewMat;
			glm::vec3 CameraPosition;
		};

		static SceneData* m_SceneData;
	};
}