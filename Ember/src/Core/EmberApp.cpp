#include "Core/EmberApp.h"

// Central Hub
// Application class creates a Window class but the Windows class 
// wont have any knowledge of Application class
// We need to message events from Windows class to Application class.

namespace Ember
{

#define BIND_EVENT_FN(func) std::bind(&EmberApp::func, this, std::placeholders::_1)

    EmberApp* EmberApp::instance = nullptr;

    EmberApp::EmberApp()
    {
        ER_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;
        
        this->m_Window = new Window();
        this->m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    EmberApp::~EmberApp()
    {
        delete this->m_Window;
    }

    void EmberApp::Run()
    {
        while (this->isRunning)
        {

            for (auto it = this->LayerStack.Begin(); it != this->LayerStack.End();)
            {
                (*it++)->OnUpdate();
            }

            this->m_Window->OnUpdate();
        }
    }

    void EmberApp::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCloseEvent));

        // Propagate events through the LayerStack from  first Layer to last Layer based on the order of insertion.
        for (auto it = this->LayerStack.End(); it != this->LayerStack.Begin(); )
        {
            // Propagate events through LayerStack.
            // Decrement the pointer first, then dereference. Otherwise faulty logic as we cannot dereference LayerStack.End().
            // --it;
            (*--it)->OnEvent(event);
            if (event.isHandled())
            {
                break;
            }
        }
    }

    bool EmberApp::OnWindowCloseEvent(WindowCloseEvent& event)
    {
        this->isRunning = false;
        return true;
    }

    void  EmberApp::PushLayer(Layer* layer)
    {
        this->LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void EmberApp::PushOverlay(Layer* overlay)
    {
        this->LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    
};