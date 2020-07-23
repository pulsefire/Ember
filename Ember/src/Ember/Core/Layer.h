#ifndef EMBER_LAYER
#define EMBER_LAYER

#include "Ember/Core/Core.h"
#include "Ember/Event/Event.h"


namespace Ember
{

    class EMBER_API Layer
    {   
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();
        // ~ Init and Shutdown
        virtual void OnAttach();
        virtual void OnDetach();

        virtual void OnUpdate();
        virtual void OnEvent(Event& event);

        virtual void OnGuiRender();
        
        inline std::string& GetName() { return this->debugName; };
    
    protected:
        std::string debugName;
    };

};







#endif