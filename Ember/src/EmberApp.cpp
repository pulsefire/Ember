#include "Ember/EmberApp.h"

// Central Hub

// Application class creates a Window class but the Windows class 
// wont have any knowledge of Application class
// We need to message events from Windows class to Application class.

namespace Ember
{

#define BIND_EVENT_FN(func) std::bind(&EmberApp::func, this, std::placeholders::_1)

    EmberApp::EmberApp()
    {
        this->m_Window = Window::Create();
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
            this->m_Window->OnUpdate();
        }
    }

    void EmberApp::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        ER_CORE_TRC(event);
    }

    bool EmberApp::OnWindowClose(WindowCloseEvent& event)
    {
        this->isRunning = false;
        return true;
    }


    
};