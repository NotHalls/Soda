#pragma once

#include "Events.h"


namespace Soda
{
    class SD_DLL KeyEvent : public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategory_Keyboard | EventCategory_Input)

        inline int GetKeyCode() const
        { return m_KeyCode; }

    protected:
        KeyEvent(int keycode)
            : m_KeyCode(keycode)
        {}

        int m_KeyCode;
    };


    class SD_DLL KeyPressedEvent : public KeyEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyPressed)

        KeyPressedEvent(int keycode, int Reapeter)
            : KeyEvent(keycode), m_Repeater(Reapeter)
        {}

        inline int GetReapeter() const
        { return m_Repeater; }

        std::string ToString() const override
        {
            std::stringstream msg;
            msg << "KeyPressedEvent: " << m_KeyCode << " (" << m_Repeater << " repeats)";
            return msg.str();
        }
        
    private:
        int m_Repeater;
    };


    class SD_DLL KeyReleasedEvent : public KeyEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyReleased)

        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode)
        {}

        std::string ToString() const override
        {
            std::stringstream msg;
            msg << "KeyReleasedEvent: " << m_KeyCode;
            return msg.str();
        }
    };
}