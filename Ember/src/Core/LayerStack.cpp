#include "Core/LayerStack.h"

namespace  Ember
{
    LayerStack::LayerStack()
    {
        this->LayerPos = 0;
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : this->Layers)
        {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        this->Layers.emplace(this->Layers.begin() + this->LayerPos, layer);
        this->LayerPos++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        this->Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(this->Layers.begin(), this->Layers.end(), layer);
        if (it != this->Layers.end())
        {
            this->Layers.erase(it);
            this->LayerPos--;
        }
    }

    void LayerStack::PopOverlay(Layer* layer)
    {
        auto it = std::find(this->Layers.begin(), this->Layers.end(), layer);
        if (it != this->Layers.end())
            this->Layers.erase(it);
    }

    std::vector<Layer*>::iterator LayerStack::Begin()
    {
        return this->Layers.begin();
    }

    std::vector<Layer*>::iterator LayerStack::End()
    {
        return this->Layers.end();
    }

};