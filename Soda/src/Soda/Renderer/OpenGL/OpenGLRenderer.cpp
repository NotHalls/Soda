#include "SD_PCH.h"

#include "OpenGLRenderer.h"

#include "glad/glad.h"
#include "glm/glm.hpp"


namespace Soda
{
	void OpenGLRenderer::ClearScreen(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void OpenGLRenderer::DrawThis(const std::shared_ptr<VertexArray>& VA)
	{
		glDrawElements(GL_TRIANGLES, VA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}