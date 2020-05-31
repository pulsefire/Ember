
#ifndef EMBER_ENTRY
#define EMBER_ENTRY

extern Ember::EmberApp* Ember::createApp();

int main(int argc, char** argv)
{
    Ember::Log::Init();

    Ember::EmberApp* app = Ember::createApp();
    app->Run();
    delete app;

    return 0;
}





#endif