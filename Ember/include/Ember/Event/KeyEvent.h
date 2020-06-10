
#ifndef EMBER_KEY_EVENT
#define EMBER_KEY_EVENT


#include "Ember/Event/Event.h"

namespace Ember
{
    class EMBER_API KeyEvent : public Event
    {
    public:

        DEFINE_EVENT_CATEGORY(InputEvent & KeyboardEvent);

        int GetKeyCode()
        {
            return this->keycode;
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

        KeyPressedEvent(int keycode, int repeatCount) 
            : KeyEvent(keycode), repeatCount(repeatCount) 
        {
            
        }

        DEFINE_EVENT_TYPE(KeyPressed);

        inline int GetRepeatCount()
        {
            return this->repeatCount;
        }

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "KeyPressedEvent: " << this->keycode << " (" << this->repeatCount << " repeats";
            return stream.str();
        }

    private:

        int repeatCount;
    };


    class EMBER_API KeyReleasedEvent : public KeyEvent
    {
    public:

        KeyReleasedEvent(int key_code) 
            : KeyEvent(key_code) 
        {

        }

        DEFINE_EVENT_TYPE(KeyReleased);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "KeyReleasedEvent: " << this->keycode;
            return stream.str();
        }
    };
};









#endif