#pragma once


namespace Soda
{
	enum class API
	{
		None = 0,
		OpenGL = 1
	};


	class RenderAPI
	{
	public:
		static void SetAPI(API api)
		{ m_whatAPI = api; }

		static API GetAPI()
		{ return m_whatAPI; }

	private:
		static API m_whatAPI;
	};
}