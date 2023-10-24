#include "SD_PCH.h"

#include "RenderAPI.h"

#include "Texture.h"

#include "Soda/Renderer/OpenGL/OpenGLTexture.h"


namespace Soda
{
	std::unique_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			SD_ENGINE_ASSERT(!nullptr, "No API Selected :/");

		case RenderAPI::API::OpenGL:
			return std::make_unique<OpenGLTexture2D>(path);
		}

		SD_ENGINE_ASSERT(!nullptr, "Invalid API :O");
		return nullptr;
	}
}