#ifndef EMBER_APP
#define EMBER_APP

#include "Ember/Core/Core.h"
#include "Ember/Core/Log.h"
#include "Ember/Event/ApplicationEvent.h"
#include "Ember/Core/Window.h"
#include "Ember/Core/LayerStack.h"


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

        Window* GetWindow();

    private:
        LayerStack LayerStack;
        Window* m_Window;        
    };

    // Returns new instance of Client Application.
    extern EmberApp* CreateApp();
};


#endif