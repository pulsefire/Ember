#ifndef EMBER_MOUSE_EVENT
#define EMBER_MOUSE_EVENT

#include "Event.h"
#include <stringstream>


namespace Ember
{


    class EMBER_API MouseButtonEvent : public Event
    {
    public:
        
        MouseButtonEvent(int button) 
            : button(button)
        {

        }

        int GetEventCategory() override
        {
            return EventCategory::MouseButtonEvent | EventCategory::InputEvent;
        }

        int GetButton()
        {
            return button;
        }

    private:

        int button;
        
    };

    class EMBER_API MousePressedEvent : public MouseButtonEvent
    {
    public:

        MousePressedEvent(int button)
            : MouseButtonEvent(button)
        {

        }

        static Event& GetStaticType()
        {
            return EventType::MousePressed;
        }

        Event& GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "MousePressed";
        }

        std::string ToString() override
        {
            std::stringstream stream;
            stream << "MousePressedEvent: " << button;
            return stream;
        }

    };


    class EMBER_API MouseReleasedEvent : public MouseButtonEvent
    {
    public:

        MouserReleasedEvent(int button)
            : MouseButtonEvent(button)
        {

        }

        static Event& GetStaticType()
        {
            return EventType::MouseReleased;
        }

        Event& GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "MouseReleased";
        }

        std::string ToString() override
        {
            std::stringstream stream;
            stream << "MouseReleasedEvent: " << button;
            return stream;
        }
    };

    class EMBER_API MouseScrolledEvent : public Event
    {
    public:

        MouseScrolledEvent(float offsetX, offsetY)
            : offsetX(offsetX), offsetY(offsetY)
        {

        }

        EventType& GetStaticType()
        {
            return EventType::MouseMoved;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "MouseMoved"
        }

        std::string ToString() override
        {
            std::stringstream stream;
            stream << "MouseMovedEvent: " << GetOffsetX() << ", " << GetOffsetY();
            return stream.str();
        }

        inline float GetOffsetX() { return offsetX; }
        inline float GetOffsetY() { return offsetY; }
        
    private:
        float offsetX, offsetY;
    };

    class EMBER_API MouseMovedEvent : public Event
    {
    public:

        MouseMovedEvent(float x, float y)
            : mouseX(x), mouseY(y)
        {

        }

        int GetEventCategory() override
        {
            return MouseEvent | InputEvent
        }

        static Event& GetStaticType()
        {
            return EventType::MouseMoved;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* Getname() override
        {
            return "MouseMovedEvent";
        }

        std::string ToString() override
        {
            std::stringstream stream;
            stream << "MouseMovedEvent: " << GetX() << ", " << GetY();
            return stream.str();
        }

        inline float GetX() { return mouseX; };
        inline float GetY() { return mouseY; };

    private:
        float mouseX, mouseY;
    }

};


#endif