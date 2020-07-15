#include "ClientApp.h"
#include <iostream>

class ExampleLayer : public Ember::Layer
{
public:
    ExampleLayer()
        : Ember::Layer("Example")
    {

    }

    void OnUpdate() override
    {
        // ER_INF("ExampleLayer::Update");
    }

    void OnEvent(Ember::Event& event) override
    {
        if (event.GetEventType() == Ember::EventType::KeyPress)
        {
            Ember::KeyPressEvent& keyevent = (Ember::KeyPressEvent&)event;
            ER_CORE_TRC("{0}", (char)keyevent.GetKeyCode());
        }
    }
};


ClientApp::ClientApp() : Ember::EmberApp()
{
    ER_CORE_ERR("Ember Core Ready!");
    ER_WRN("Welcome to Ember Application!");

    this->PushLayer(new ExampleLayer());
    this->PushOverlay(new Ember::GuiLayer());
}

ClientApp::~ClientApp()
{

}

Ember::EmberApp* Ember::CreateApp()
{
    return new ClientApp();
}