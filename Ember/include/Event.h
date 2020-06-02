#ifndef EMBER_EVENT
#define EMBER_EVENT

#include "Core.h"

#include <string>
#include <functional>

namespace Ember
{

    // Implementation of blocking events. 

    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, // Key held event is KeyPressed 
        MousePressed, MouseReleased, MouseMoved, MouseScrolled,
    };
    

    enum EventCategory
    {
        None = 0,
        ApplicationEvent = (1 << 0), // 000001
        InputEvent       = (1 << 1), // 000010
        KeyboardEvent    = (1 << 2), // 000100
        MouseEvent       = (1 << 3), // 010000
        MouseButtonEvent = (1 << 4), // 100000
        // This is event category bit field.
        // We can check to what category an event belongs to based on the set bits.
        // Example
        // MouseButtonEvent is both an InputEvent and MouseEvent so its bitfeld will look like 110010.
    };

// #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::#type;}\
//                                virtual EventType GetEventType() { return GetStaticType(); }\
//                                virtual const char* GetName() const override { return #type; }

// #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

    class EMBER_API Event
    {
    public:
        // Access private members of Event so
        // each event can be dispached.
        friend class EventDispatcher;

        virtual EventType GetEventType() = 0;

        // If for example KeyboardEvent, will return a bit map 00111.
        virtual int GetEventCategory() = 0;
        
        virtual const char* GetName() = 0;
        // Hint the compiler that ToString may be overriden.
        virtual std::string ToString()
        {
            return this->GetName();
        }

        bool IsInCategory(EventCategory& category)
        {
            // Check if event is in a given category by and-ing for example some MouseEventCategory
            // which is 01111 with 01000 MouseEventCategory and return true.
            return this->GetEventCategory() & category;
        }
        
    protected:

        bool handled = false;
    };

    class EMBER_API EventDispatcher
    {
    public:
        // Friend to Event Class.
        // Signature that points to a method taking EventType parameter and returning bool.
        template <typename T>
        using EventFunc = std::function<bool(T&)>;

        EventDispatcher(Event& event) 
            : event(event) 
        {

        }

        template <typename T>
        bool Dispatch(EventFunc<T> func)
        {
            if (this->event.GetEventType() == T::GetStaticType())
            {

            }
        }

    private:

        Event& event;
    };





    




};

#endif