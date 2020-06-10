#ifndef EMBER_MOUSE_EVENT
#define EMBER_MOUSE_EVENT

#include "Ember/Event/Event.h"

namespace Ember
{
    class EMBER_API MouseButtonEvent : public Event
    {
    public:
        
        MouseButtonEvent(int mouseButton) 
            : mouseButton(mouseButton)
        {

        }

        DEFINE_EVENT_CATEGORY(InputEvent & MouseEvent);

        int GetMouseButton()
        {
            return mouseButton;
        }

    protected:
        int mouseButton;
    };

    class EMBER_API MousePressedEvent : public MouseButtonEvent
    {
    public:

        MousePressedEvent(int button)
            : MouseButtonEvent(button)
        {

        }

        DEFINE_EVENT_TYPE(MousePressed);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "MousePressedEvent: " << mouseButton;
            return stream.str();
        }

    };


    class EMBER_API MouseReleasedEvent : public MouseButtonEvent
    {
    public:

        MouseReleasedEvent(int button)
            : MouseButtonEvent(button)
        {

        }

        DEFINE_EVENT_TYPE(MouseReleased);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "MouseReleasedEvent: " << mouseButton;
            return stream.str();
        }
    };

    class EMBER_API MouseScrolledEvent : public Event
    {
    public:

        MouseScrolledEvent(float offsetX, float offsetY)
            : offsetX(offsetX), offsetY(offsetY)
        {

        }

        DEFINE_EVENT_TYPE(MouseScrolled);
        DEFINE_EVENT_CATEGORY(InputEvent & MouseEvent);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "MouseScrolledEvent: " << GetOffsetX() << ", " << GetOffsetY();
            return stream.str();
        }

        inline float GetOffsetX() const { return offsetX; }
        inline float GetOffsetY() const { return offsetY; }
        
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
        
        DEFINE_EVENT_TYPE(MouseMoved);
        DEFINE_EVENT_CATEGORY(InputEvent & MouseEvent);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "MouseMovedEvent: " << GetX() << ", " << GetY();
            return stream.str();
        }

        inline float GetX() const { return mouseX; };
        inline float GetY() const { return mouseY; };

    private:
        float mouseX, mouseY;
    };

};


#endif