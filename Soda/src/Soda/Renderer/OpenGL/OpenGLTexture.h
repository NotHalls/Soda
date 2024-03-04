#pragma once

#include "Soda/Renderer/Texture.h"


namespace Soda
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual void Bind(uint32_t slot = 0) override;
		virtual void Unbind(uint32_t slot) override;

		virtual unsigned int GetWidth() const override
		{ return m_Width; }
		virtual unsigned int GetHeight() const override
		{ return m_Height; }

		virtual const float GetTextureScale() const override
		{ return m_TextureScale; }
		virtual const void SetTextureScale(const float texScale) override
		{ m_TextureScale = texScale; }

		virtual const glm::vec4& GetTextureTint() const override
		{ return m_TextureTint; }
		virtual const void SetTextureTint(const glm::vec4& tint) override
		{ m_TextureTint = tint; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual const std::string& GetFilePath() const override
		{ return m_Path; }
		virtual const uint32_t GetTextureID() const override
		{ return m_TextureID; }

		virtual const bool operator==(const Textrue& texture) const override
		{
			return m_TextureID == ((OpenGLTexture2D&)texture).m_TextureID;
		}

	private:
		uint32_t m_Width, m_Height;
		std::string m_Path;
		uint32_t m_TextureID;

		float m_TextureScale;
		glm::vec4 m_TextureTint;

		int m_DataFormat, m_InternalFormat;
	};
}