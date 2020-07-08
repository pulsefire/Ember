#ifndef EMBER_APP_EVENT
#define EMBER_APP_EVENT

#include "Ember/Event/Event.h"

namespace Ember
{
    class EMBER_API WindowResizeEvent : public Event
    {
    public:

        WindowResizeEvent(int w, int h)
            : width(w), height(h)
        {
            
        }

        DEFINE_EVENT_TYPE(WindowResize);
        DEFINE_EVENT_CATEGORY(ApplicationEvent);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "WindowResizeEvent: " << width << ", " << height;
            return stream.str();
            // return "WindowResizeEvent: " + std::to_string(width) + ", " + std::to_string(height);
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

        DEFINE_EVENT_TYPE(WindowClose);
        DEFINE_EVENT_CATEGORY(ApplicationEvent)

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "WindowCloseEvent";
            return stream.str();
        }
    };

    class EMBER_API AppTickEvent : public Event
    {
    public:

        AppTickEvent() 
        {

        }

        DEFINE_EVENT_TYPE(AppTick);
        DEFINE_EVENT_CATEGORY(ApplicationEvent);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "AppTickEvent";
            return stream.str();
        }
    };

    class EMBER_API AppUpdateEvent : public Event
    {
    public:

        AppUpdateEvent()
        {

        }

        DEFINE_EVENT_TYPE(AppUpdate);
        DEFINE_EVENT_CATEGORY(ApplicationEvent);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "AppUpdateEvent";
            return stream.str();
        }
    };

    class EMBER_API AppRenderEvent : public Event
    {
    public:

        AppRenderEvent()
        {

        }
        DEFINE_EVENT_TYPE(AppRender);
        DEFINE_EVENT_CATEGORY(ApplicationEvent);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "AppRenderEvent";
            return stream.str();
        }
    };
};

#endif