#pragma once

#include "SD_PCH.h"

#include "Soda/Renderer/Bufferer.h"


namespace Soda
{
	class VertexArray
	{
	public:
		VertexArray() {}
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}