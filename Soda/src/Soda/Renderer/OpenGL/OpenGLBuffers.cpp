#include "SD_PCH.h"

#include "OpenGLBuffer.h"

#include "glad/glad.h"


namespace Soda
{
	/*****************************************************************/
	/* Index Index ***************************************************/
	/*****************************************************************/

	GLVertexBuffer::GLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);

		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	GLVertexBuffer::~GLVertexBuffer()
	{
		glDeleteBuffers(1, &m_bufferID);
	}


	void GLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	}

	void GLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_VERTEX_ARRAY, 0);
	}


	/*****************************************************************/
	/* Index Buffer **************************************************/
	/*****************************************************************/

	GLIndexBuffer::GLIndexBuffer(int* indices, uint32_t size)
	{
		glCreateBuffers(1, &m_bufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	GLIndexBuffer::~GLIndexBuffer()
	{
		glDeleteBuffers(1, &m_bufferID);
	}


	void GLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
	}

	void GLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}