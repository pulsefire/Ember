#ifndef EMBER_APP
#define EMBER_APP

#include "Ember/Core.h"
#include "Ember/Log.h"
#include "Ember/Event/ApplicationEvent.h"
#include "Ember/Window.h"


namespace Ember
{
    class EMBER_API EmberApp
    {
    public:

        EmberApp();
        virtual ~EmberApp();
        
        void Run();
        void OnEvent(Event& event);
        bool OnWindowClose(WindowCloseEvent& event);

        bool isRunning = true;
        Window* m_Window;
    };

    // Returns new instance of Client Application.
    extern EmberApp* CreateApp();

};


#endif