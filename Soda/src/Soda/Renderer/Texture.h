#pragma once

#include "Soda/Core.h"


namespace Soda
{
	class Textrue
	{
	public:
		virtual ~Textrue() = default;

		virtual void Bind(uint32_t slot = 0) = 0;
		virtual void Unbind(uint32_t slot) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual const std::string& GetFilePath() const = 0;
		virtual const uint32_t GetTextureID() const = 0;
	};


	class Texture2D : public Textrue
	{
	public:
		virtual ~Texture2D() = default;

		static std::unique_ptr<Texture2D> Create(const std::string& path);
	};
}