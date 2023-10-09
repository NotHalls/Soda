#pragma once


namespace Soda
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(float* vertices, uint32_t size);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};


	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(int* indices, uint32_t size);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};
}