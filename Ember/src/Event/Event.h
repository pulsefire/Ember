#ifndef EMBER_EVENT
#define EMBER_EVENT

#include <string>
#include <sstream>
#include <functional>

#include "Core/Core.h"

#define SPDLOG_COMPILED_LIB
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"



namespace Ember
{

    // Implementation of blocking events.
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPress, KeyRelease, KeyType, // Key held event is KeyPress Event 
        MousePress, MouseRelease, MouseMove, MouseScroll
    };

    enum EventCategory
    {
        None = 0,
        ApplicationEvent = (1 << 0), // 000001
        InputEvent       = (1 << 1), // 000010
        KeyboardEvent    = (1 << 2), // 000100
        MouseEvent       = (1 << 3), // 010000
        MouseButtonEvent = (1 << 4), // 100000
        /*  Event category bit field.
            We can check to what category an event belongs to based on the set bits.
            Example :
            MouseButtonEvent is both an InputEvent and MouseEvent so its bitfeld will look like 110010.
        */
    };

    class EMBER_API Event
    {
    public:
        virtual EventType GetEventType() = 0;
        virtual int GetEventCategory() const = 0;
        virtual const char* GetName() const = 0;

        friend class EventDispatcher;
        
        virtual std::string ToString() const
        {
            return this->GetName();
        }

        bool IsInCategory(EventCategory& category)
        {
            return this->GetEventCategory() & category;
        }

        bool isHandled()
        {
            return this->handled;
        }

        void Handle()
        {
            this->handled = true;
        }

    protected:
        bool handled = false;
    };

#define DEFINE_EVENT_TYPE(type) static EventType GetStaticType() { return EventType::type;}; \
                                virtual EventType GetEventType() { return GetStaticType(); }; \
                                virtual const char* GetName() const override { return #type; }

#define DEFINE_EVENT_CATEGORY(category) virtual int GetEventCategory() const override {return category; }


    class EMBER_API EventDispatcher
    {
    public:
        // Friend to Event Class.
        // Signature that points to a method taking EventType parameter and returning bool.
        // The alias template
        // This is better than typedef because we can implement functions that recieve specific events
        // and invoke them automatically from the EventDispatcher
        // Better than typedef as we can pass any Event type to the Dispatch function.
        template <typename T>
        using EventFnType = std::function<bool(T&)>;

        EventDispatcher(Event& event) 
            : event(event) 
        {

        }

        template <typename T>
        bool Dispatch(const EventFnType<T>& Func)
        {
            if (this->event.GetEventType() == T::GetStaticType())
            {
                event.handled = Func(*(T*)&event);
                return true;
            }
            return false;
        }

    private:
        Event& event;
    };

    inline std::ostream& operator<< (std::ostream& os, const Event& event)
    {
        return os << event.ToString();
    }
};

#endif