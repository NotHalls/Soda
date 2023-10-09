#pragma once

#include "Soda/Renderer/Bufferer.h"


namespace Soda
{
	class GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* vertices, uint32_t size);
		~GLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		
	private:
		uint32_t m_bufferID;
	};

	class GLIndexBuffer : public IndexBuffer
	{
	public:
		GLIndexBuffer(int* indices, uint32_t size);
		~GLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

	private:
		uint32_t m_bufferID;
	};
}