#pragma once

#include "Events.h"


namespace Soda
{
	class SD_DLL WindowResizeEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategory_App)

		WindowResizeEvent(unsigned int wWidth, unsigned int wHeight)
			: m_windowWidth(wWidth), m_windowHeight(wHeight)
		{}

		inline unsigned int GetWindowWidth() const
		{ return m_windowWidth; }
		inline unsigned int GetWindowHeight() const
		{ return m_windowHeight; }

		std::string ToString() const override
		{
			std::stringstream msg;
			msg << "Window Resized To (Width: " << m_windowWidth << ", Height: " << m_windowHeight << ")";
			return msg.str();
		}

	private:
		unsigned int m_windowWidth, m_windowHeight;
	};

	class SD_DLL WindowCloseEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategory_App)

		WindowCloseEvent()
		{}
	};


	class SD_DLL AppTickEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategory_App)

		AppTickEvent()
		{}
	};

	class SD_DLL AppUpdateEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategory_App)

		AppUpdateEvent()
		{}
	};

	class SD_DLL AppRenderEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategory_App)

		AppRenderEvent()
		{}
	};
}