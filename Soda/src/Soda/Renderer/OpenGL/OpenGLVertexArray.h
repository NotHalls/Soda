#pragma once

#include "Soda/Renderer/VertexArray.h"


namespace Soda
{
	class GLVertexArray : public VertexArray
	{
	public:
		GLVertexArray();
		virtual ~GLVertexArray() {}

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override
		{ return m_vertexBuffers; }
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override
		{ return m_indexBuffer; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer;

		uint32_t m_bufferID;
	};
}