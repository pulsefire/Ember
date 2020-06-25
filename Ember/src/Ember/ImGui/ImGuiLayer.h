#ifndef EMBER_GUI_LAYER
#define EMBER_GUI_LAYER

#include "Ember/Core/Core.h"
#include "Ember/Core/Layer.h"
#include "Ember/Event/Event.h"
#include "Ember/Core/EmberApp.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Ember
{

    class EMBER_API ImGuiLayer : Layer
    {   
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event);
    };

};





#endif