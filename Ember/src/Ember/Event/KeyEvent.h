
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


    class EMBER_API KeyPressEvent : public KeyEvent
    {
    public:

        KeyPressEvent(int keycode, int repeatCount) 
            : KeyEvent(keycode), repeatCount(repeatCount) 
        {
            
        }

        DEFINE_EVENT_TYPE(KeyPress);

        inline int GetRepeatCount()
        {
            return this->repeatCount;
        }

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "KeyPressEvent: " << this->keycode << " (" << this->repeatCount << " repeats)";
            return stream.str();
        }

    private:

        int repeatCount;
    };


    class EMBER_API KeyReleaseEvent : public KeyEvent
    {
    public:

        KeyReleaseEvent(int key_code) 
            : KeyEvent(key_code) 
        {

        }

        DEFINE_EVENT_TYPE(KeyRelease);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "KeyReleaseEvent: " << this->keycode;
            return stream.str();
        }
    };

    class EMBER_API KeyTypeEvent : public KeyEvent
    {
    public:
        KeyTypeEvent(int keycode)
            : KeyEvent(keycode)
        {

        }

        DEFINE_EVENT_TYPE(KeyType);

        virtual std::string ToString() const override
        {
            std::stringstream stream;
            stream << "KeyTypeEvent: " << this->keycode;
            return stream.str();
        }
    };

};









#endif