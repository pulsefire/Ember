#include "ClientApp.h"
#include <iostream>

class ExampleLayer : public Ember::Layer
{
public:
    ExampleLayer()
        : Ember::Layer("Example")
    {

    }

    ~ExampleLayer()
    {

    }

    void OnUpdate() override
    {

    }

    void OnEvent(Ember::Event& event) override
    {
        // ER_TRC(event);
    }

    void OnAttach()
    {

    }

    void OnDetach()
    {

    }

};


ClientApp::ClientApp() : Ember::EmberApp()
{
    ER_CORE_ERR("Ember Core Ready!");
    ER_WRN("Welcome to Ember Application!");

    this->PushLayer(new ExampleLayer());
}

ClientApp::~ClientApp()
{
    
}

Ember::EmberApp* Ember::CreateApp()
{
    return new ClientApp();
}