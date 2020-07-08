
#ifndef EMBER_ENTRY
#define EMBER_ENTRY

extern Ember::EmberApp* Ember::CreateApp();

int main(int argc, char** argv)
{
    Ember::Log::Init();

    Ember::EmberApp* app = Ember::CreateApp();
    app->Run();
    delete app;

    return 0;
}





#endif