#ifndef EMBER_APP
#define EMBER_APP

#include "Core/Core.h"
#include "Core/Log.h"
#include "Event/ApplicationEvent.h"
#include "Core/Window.h"
#include "Core/LayerStack.h"


namespace Ember
{
    class EMBER_API EmberApp
    {
    public:

        EmberApp();
        virtual ~EmberApp();
        
        void Run();
        void OnEvent(Event& event);
        bool OnWindowCloseEvent(WindowCloseEvent& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        bool isRunning = true;

        static EmberApp* instance;
        static inline EmberApp& Get() { return *instance; };

        LayerStack LayerStack;
        Window* m_Window;        
    };

    // Returns new instance of Client Application.
    extern EmberApp* CreateApp();
};


#endif