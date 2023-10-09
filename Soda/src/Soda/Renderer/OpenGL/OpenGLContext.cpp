#include "SD_PCH.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "OpenGLContext.h"


namespace Soda
{
	void SodaGL::Init()
	{
		// initializing GLAD
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SD_ENGINE_ASSERT(status, "Failed to initialize GLAD!");
	}
}