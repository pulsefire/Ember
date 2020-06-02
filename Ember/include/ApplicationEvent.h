#ifndef EMBER_APP_EVENT
#define EMBER_APP_EVENT

#include "Event.h"


namespace Ember
{
    class EMBER_API WindowResizeEvent : public Event
    {
    public:

        WindowResizeEvent(int w, int h)
            : width(w), height(h)
        {
            
        }

        static EventType GetStaticType()
        {
            return EventType::WindowResize;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "WindowResize"
        }

        int GetEventCategory() override
        {
            return EventCategory::ApplicationEvent;
        }

    private:

        int width, height;
    };


    class EMBER_API WindowCloseEvent : public Event
    {
    public:

        WindowCloseEvent()
        {

        }

        static EventType GetStaticType()
        {
            return EventType::WindowClose;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "WindowClose"
        }

        int GetEventCategory() override
        {
            return EventCategory::ApplicationEvent;
        }
    };

    class EMBER_API AppTickEvent : public Event
    {
    public:

        AppTickEvent() 
        {

        }

        static EventType GetStaticType()
        {
            return EventType::AppTick;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "AppTick"
        }

        int GetEventCategory() override
        {
            return EventCategory::ApplicationEvent;
        }
    };

    class EMBER_API AppUpdateEvent : public Event
    {
    public:

        AppUpdateEvent()
        {

        }

        static EventType GetStaticType()
        {
            return EventType::AppUpdate;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "AppUpdate"
        }

        int GetEventCategory() override
        {
            return EventCategory::ApplicationEvent;
        }
    };

    class EMBER_API AppRenderEvent : public Event
    {
    public:

        AppRenderEvent()
        {

        }

        static EventType GetStaticType()
        {
            return EventType::AppRender;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "AppRender"
        }

        int GetEventCategory() override
        {
            return EventCategory::ApplicationEvent;
        }
    }





};

#endif