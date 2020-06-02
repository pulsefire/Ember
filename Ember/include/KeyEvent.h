
#ifndef EMBER_KEY_EVENT
#define EMBER_KEY_EVENT


#include "Event.h"
#include <stringstream>


namespace Ember
{
    class EMBER_API KeyEvent : public Event
    {
    public:

        int GetKeyCode()
        {
            return this->keycode;
        }

        virtual int GetEventCategory()
        {
            return InputEvent | KeyboardEvent; 
        }

    protected:
        
        KeyEvent(int keycode) 
            : keycode(keycode) 
        {

        }

        int keycode;
    };


    class EMBER_API KeyPressedEvent : public KeyEvent
    {
    public:

        KeyPressedEvent(int keycode, int repeat_count) 
            : KeyEvent(keycode), repeat_count(repeat_count) 
        {
            
        }

        inline int GetRepeatCount()
        {
            return this->repeat_count;
        }

        static EventType GetStaticType()
        {
            return EventType::KeyPressed;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "KeyPressed";
        }

        std::string ToString() override
        {
            std::stringstream stream;
            stream << "KeyPressedEvent: " << this->keycode << " (" << this->repeat_count << " repeats";
            return stream.str();
        }

    private:

        int repeat_count;
    };


    class EMBER_API KeyReleasedEvent : public KeyEvent
    {
    public:

        KeyReleasedEvent(int key_code) 
            : KeyEvent(key_code) {}

        static EventType GetStaticType()
        {
            return EventType::KeyReleased;
        }

        EventType GetEventType() override
        {
            return GetStaticType();
        }

        const char* GetName() override
        {
            return "KeyReleased";
        }

        std::string ToString() override
        {
            std::stringstream stream;
            stream << "KeyReleasedEvent: " << this->key_code;
            return stream.str();
        }
    };





};









#endif