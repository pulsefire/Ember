#ifndef EMBER_GUI_LAYER
#define EMBER_GUI_LAYER

#include "Ember/Core/Core.h"
#include "Ember/Core/Layer.h"

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include "glad/glad.h"


namespace Ember
{

    class EMBER_API GuiLayer : public Layer
    {   
    public:
        GuiLayer();
        ~GuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnGuiRender() override;

        void Begin();
        void End();
    };

};





#endif