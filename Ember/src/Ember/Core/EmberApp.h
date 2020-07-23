#ifndef EMBER_APP
#define EMBER_APP

#include "Ember/Core/Core.h"
#include "Ember/Core/Log.h"
#include "Ember/Core/Window.h"
#include "Ember/Core/LayerStack.h"

#include "Ember/Core/Layer.h"
#include "Ember/Gui/GuiLayer.h"

#include "Ember/Event/ApplicationEvent.h"

#include "Ember/Renderer/Buffer.h"
#include "Ember/Renderer/Shader.h"


namespace Ember
{
    class EMBER_API EmberApp
    {
    public:

        EmberApp();
        virtual ~EmberApp();
        
        void Run();
        void OnEvent(Event& event);
        
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        static inline EmberApp& Get() { return *instance; };

        Window* GetWindow();

    private:
        bool OnWindowCloseEvent(WindowCloseEvent& event);
        bool isRunning = true; 

        Window* m_Window;     
        LayerStack LayerStack;
        GuiLayer* m_GuiLayer;  
        Shader* m_Shader;
        
        unsigned int m_VertexArray; //, m_IndexBuffer, m_VertexBuffer;
        VertexBuffer* m_VertexBuffer;
        IndexBuffer* m_IndexBuffer;

    private:
        static EmberApp* instance;
    };

    // Returns new instance of Client Application.
    extern EmberApp* CreateApp();
};


#endif