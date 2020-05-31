#include "ClientApp.h"
#include <iostream>

ClientApp::ClientApp() : Ember::EmberApp()
{
    ER_CORE_INF("Ember Core Ready!");
    ER_WRN("Welcome to Ember Application!");
    ER_ERR("Hello!");
    ER_ERR("Hello!");
    std::cin.get();
}

ClientApp::~ClientApp()
{

}

Ember::EmberApp* Ember::createApp()
{
    return new ClientApp();
}