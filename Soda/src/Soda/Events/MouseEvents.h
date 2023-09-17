#pragma once

#include "Events.h"


namespace Soda
{
	class SD_DLL MouseMoveEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseMove)
		EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input)


		MouseMoveEvent(float xPos, float yPos)
			: m_MouseX(xPos), m_MouseY(yPos)
		{}

		inline float GetMouseX() const
		{ return m_MouseX; }
		inline float GetMouseY() const
		{ return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream msg;
			msg << "MouseAt: " << "(x: " << m_MouseX << ", y: " << m_MouseY << ")";
			return msg.str();
		}

	private:
		float m_MouseX, m_MouseY;
	};


	class SD_DLL MouseScrollEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseScroll)
			EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input)

			MouseScrollEvent(float xOffset, float yOffset)
			: m_WheelOffsetX(xOffset), m_WheelOffsetY(yOffset)
		{}

		inline float GetWheelOffsetX() const
		{
			return m_WheelOffsetX;
		}
		inline float GetWheelOffsetY() const
		{
			return m_WheelOffsetY;
		}

	private:
		float m_WheelOffsetX, m_WheelOffsetY;
	};


	class SD_DLL MouseButtonEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input)

		int GetButtonClicked() const
		{ return m_MouseButton; }

	protected:
		MouseButtonEvent(int mouseButton)
			: m_MouseButton(mouseButton)
		{}

		int m_MouseButton;
	};

	class SD_DLL MouseClickedEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseClick)

		MouseClickedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton)
		{}

		std::string ToString() const override
		{
			std::stringstream msg;
			msg << "MouseClicked: " << m_MouseButton;
			return msg.str();
		}
	};

	class SD_DLL MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseRelease)

		MouseReleasedEvent(int mouseButton)
			: MouseButtonEvent(mouseButton)
		{}

		std::string ToString() const override
		{
			std::stringstream msg;
			msg << "MouseReleased: " << m_MouseButton;
			return msg.str();
		}
	};
}