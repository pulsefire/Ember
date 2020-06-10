#ifndef EMBER_APP
#define EMBER_APP

#include "Ember/Core.h"
#include "Ember/Log.h"
#include "Ember/Event/ApplicationEvent.h"


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
    extern EmberApp* CreateApp();

};


#endif