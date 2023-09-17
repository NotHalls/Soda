#pragma once

#include "SD_PCH.h"

#include "Soda/Core.h"


namespace Soda
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowNoFocus, WindowMove,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseClick, MouseRelease, MouseMove, MouseScroll
    };

    enum EventCategory
    {
        None = 0,
        EventCategory_App           = BIT(0),
        EventCategory_Input         = BIT(1),
        EventCategory_Keyboard      = BIT(2),
        EventCategory_Mouse         = BIT(3),
        EventCategory_MouseButton   = BIT(4)
    };


    class SD_DLL Event
    {
        friend class EventDispatcher;
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }


        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    protected:
        bool m_Handled = false;
    };


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


    class EventDispatcher
    {
        template<typename ET> // ET for Event Type
        using EventFn = std::function<bool(ET&)>;
    
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {}

        template<typename ET>
        bool Dispatch(EventFn<ET> fn)
        {
            if(m_Event.GetEventType() == ET::GetStaticType())
            {
                m_Event.m_Handled = fn(*(ET*)&m_Event);
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };


    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}