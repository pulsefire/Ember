#ifndef EMBER_GUI_LAYER
#define EMBER_GUI_LAYER

#include "Ember/Core/Core.h"
#include "Ember/Core/Layer.h"
#include "Ember/Event/Event.h"
#include "Ember/Core/EmberApp.h"

#include "imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "glad/glad.h"


namespace Ember
{

    class EMBER_API GuiLayer : public Layer
    {   
    public:
        GuiLayer();
        ~GuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event);
    
    private:
    
        bool OnMousePressEvent(MousePressEvent& event);
        bool OnMouseReleaseEvent(MouseReleaseEvent& event);
        bool OnMouseMoveEvent(MouseMoveEvent& event);
        bool OnMouseScrollEvent(MouseScrollEvent& event);
        bool OnKeyPressEvent(KeyPressEvent& event);
        bool OnKeyReleaseEvent(KeyReleaseEvent& event);
        bool OnKeyTypeEvent(KeyTypeEvent& event);
        bool OnWindowResizeEvent(WindowResizeEvent& event);
        
    protected:
        float m_Time;
        ImFont* cambria;
    };

};





#endif