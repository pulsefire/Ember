#include "ClientApp.h"
#include <iostream>

ClientApp::ClientApp() : Ember::EmberApp()
{
    ER_CORE_ERR("Ember Core Ready!");
    ER_WRN("Welcome to Ember Application!");
}

ClientApp::~ClientApp()
{

}

Ember::EmberApp* Ember::CreateApp()
{
    return new ClientApp();
}