#ifndef EMBER_LAYER
#define EMBER_LAYER

#include "Core/Core.h"
#include "Event/Event.h"


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
        
        inline std::string& GetName() { return this->debugName; };
    
    protected:
        std::string debugName;
    };

};







#endif