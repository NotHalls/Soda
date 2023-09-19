#pragma once

#include"SD_PCH.h"

#include "Core.h"
#include "Events/Events.h"


namespace Soda
{
	struct WindowInfo
	{
		std::string Name;
		unsigned int Width;
		unsigned int Height;

		WindowInfo( const std::string& p_Name = "Soda Engine",
					unsigned int p_Width = 1280,
					unsigned int p_Height = 720 )
			: Name(p_Name), Width(p_Width), Height(p_Height)
		{}
	};


	// the window class
	class SD_DLL SodaWindow
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~SodaWindow()
		{}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWindowWidth() const = 0;
		virtual unsigned int GetWindowHeight() const = 0;

		virtual void SetCallbackFn(const EventCallbackFn& CallbackFn) = 0;
		virtual void SetVSync(bool status) = 0;
		virtual bool GetVSyncStatus() const = 0;

		static SodaWindow* Create(const WindowInfo& props = WindowInfo());
	};
}