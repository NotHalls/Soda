#include "SD_PCH.h"

#include "RenderAPI.h"
#include "Bufferer.h"

#include "OpenGL/OpenGLBuffer.h"


namespace Soda
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
		case API::None:
			SD_ENGINE_ASSERT(!nullptr, "No API Selected :/");
		
		case API::OpenGL:
			return new GLVertexBuffer(vertices, size);
		}
	}

	IndexBuffer* IndexBuffer::Create(int* indices, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
		case API::None:
			SD_ENGINE_ASSERT(!nullptr, "No API Selected :/");

		case API::OpenGL:
			return new GLIndexBuffer(indices, size);
		}
	}
}