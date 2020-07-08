#ifndef EMBER_MOUSE_EVENT
#define EMBER_MOUSE_EVENT

#include "Event/Event.h"

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

    class EMBER_API MousePressEvent : public MouseButtonEvent
    {
    public:

        MousePressEvent(int button)
            : MouseButtonEvent(button)
        {

        }

        DEFINE_EVENT_TYPE(MousePress);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "MousePressEvent: " << mouseButton;
            return stream.str();
        }

    };


    class EMBER_API MouseReleaseEvent : public MouseButtonEvent
    {
    public:

        MouseReleaseEvent(int button)
            : MouseButtonEvent(button)
        {

        }

        DEFINE_EVENT_TYPE(MouseRelease);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "MouseReleasedEvent: " << mouseButton;
            return stream.str();
        }
    };

    class EMBER_API MouseScrollEvent : public Event
    {
    public:

        MouseScrollEvent(float offsetX, float offsetY)
            : offsetX(offsetX), offsetY(offsetY)
        {

        }

        DEFINE_EVENT_TYPE(MouseScroll);
        DEFINE_EVENT_CATEGORY(InputEvent & MouseEvent);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "MouseScrollEvent: " << GetOffsetX() << ", " << GetOffsetY();
            return stream.str();
        }

        inline float GetOffsetX() const { return offsetX; }
        inline float GetOffsetY() const { return offsetY; }
        
    private:
        float offsetX, offsetY;
    };

    class EMBER_API MouseMoveEvent : public Event
    {
    public:

        MouseMoveEvent(float x, float y)
            : mouseX(x), mouseY(y)
        {

        }
        
        DEFINE_EVENT_TYPE(MouseMove);
        DEFINE_EVENT_CATEGORY(InputEvent & MouseEvent);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "MouseMoveEvent: " << GetX() << ", " << GetY();
            return stream.str();
        }

        inline float GetX() const { return mouseX; };
        inline float GetY() const { return mouseY; };

    private:
        float mouseX, mouseY;
    };

};


#endif