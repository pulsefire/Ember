#include "ClientApp.h"
#include <iostream>

ClientApp::ClientApp() : Ember::EmberApp()
{
    ER_CORE_INF("Ember Core Ready!");
    ER_WRN("Welcome to Ember Application!");
    
    std::cin.get();
}

ClientApp::~ClientApp()
{

}

Ember::EmberApp* Ember::createApp()
{
    return new ClientApp();
}