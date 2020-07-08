#ifndef EMBER_LAYER_STACK
#define EMBER_LAYER_STACK

#include <vector>

#include "Ember/Core/Core.h"
#include "Ember/Core/Layer.h"

namespace Ember
{

class EMBER_API LayerStack
{
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* Layer);
        void PushOverlay(Layer* Overlay);
        void PopLayer(Layer* Layer);
        void PopOverlay(Layer* Overlay);

        std::vector<Layer*>::iterator Begin();
        std::vector<Layer*>::iterator End();

    private:

        std::vector<Layer*> Layers;
        unsigned int LayerPos;
    };
}


#endif