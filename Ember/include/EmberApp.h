#ifndef EMBER_APP
#define EMBER_APP

#include "Core.h"
#include "Log.h"
#include "ApplicationEvent.h"


namespace Ember
{
    class EMBER_API EmberApp
    {
    public:

        EmberApp();

        virtual ~EmberApp();

        void Run();
    };

    // Returns an instance of Client Application.
    extern EmberApp* createApp();

};


#endif