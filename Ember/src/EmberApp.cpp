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
        
    }

    void EmberApp::Run()
    {
        while (true)
        {
            this->m_Window->OnUpdate();
        }
    }

    void EmberApp::OnEvent(Event& event)
    {
        ER_CORE_INF(event);
    }

    // Returns new instance of Window.
    Window* Window::Create(const WindowData& data)
    {
        return new Window(data);
    }
    
};