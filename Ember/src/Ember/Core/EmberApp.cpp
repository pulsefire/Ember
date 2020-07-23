#include "Ember/Core/EmberApp.h"

// Central Hub
// Application class creates a Window class but the Windows class 
// wont have any knowledge of Application class
// We need to message events from Windows class to Application class.

#include <iostream>

namespace Ember
{

#define BIND_EVENT_FN(func) std::bind(&EmberApp::func, this, std::placeholders::_1)

    EmberApp* EmberApp::instance = nullptr;

    static GLenum ShaderToGLBaseDataType(ShaderDataType& Type)
    {
        switch (Type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Bool:   return GL_BOOL;
        }
    };

    EmberApp::EmberApp()
    {
        ER_CORE_ASSERT(!instance, "Application already exists!");
        instance = this;
        
        this->m_Window = new Window();
        this->m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        this->m_GuiLayer = new GuiLayer();
        PushOverlay(m_GuiLayer);

        //////////////////////

        // float vertices[18] = 
        // {
        //    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        //     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        //     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
        // };

        unsigned int indices[3] =
        {
            0,1,2
        };

        float vertices[15] = 
        {
           -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f
        };

        // std::cout << sizeof(vertices) << std::endl;

        
        // glGenVertexArrays(1, &m_VertexArray);
        // glBindVertexArray(m_VertexArray);

        // glGenBuffers(1, &m_VertexBuffer);
        // glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // glEnableVertexAttribArray(0);
        // glEnableVertexAttribArray(1);

        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(12));

        // glGenBuffers(1, &m_IndexBuffer);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        BufferLayout layout = 
        {
            { ShaderDataType::Float3, "a_Position", false },
            { ShaderDataType::Float2, "a_Color" , false }
        };

        glCreateVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
        m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        unsigned int idx = 0;
        for (auto& element : layout)
        {
            glEnableVertexAttribArray(idx);
            glVertexAttribPointer(idx, element.GetComponentCount(), ShaderToGLBaseDataType(element.Type), (element.Normalised ? GL_TRUE : GL_FALSE), layout.GetStride(), (const void*)element.Offset);
            idx++;
        }

        

        std::string vertexSrc = R"(
            #version 330
            
            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec2 a_Color;
            out vec4 m_Color;

            void main()
            {
                gl_Position = vec4(a_Position, 1.0);
                m_Color = vec4(a_Color, 1.0, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330

            out vec4 Color;
            in vec4 m_Color;

            void main()
            {
                Color = m_Color;
            }
        )";

        m_Shader = Shader::Create(vertexSrc, fragmentSrc);
    }

    EmberApp::~EmberApp()
    {
        delete this->m_Window;

        this->LayerStack.PopOverlay(m_GuiLayer);
        this->m_GuiLayer->OnDetach();
        
        delete this->m_GuiLayer;
    }

    void EmberApp::Run()
    {
        while (this->isRunning)
        {
            glClearColor(.1,.1,.1,1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);





            for (auto it = this->LayerStack.Begin(); it != this->LayerStack.End();)
            {
                (*it++)->OnUpdate();
            }

            this->m_GuiLayer->Begin();
            for (auto it = this->LayerStack.Begin(); it != this->LayerStack.End();)
            {
                (*it++)->OnGuiRender();
            }
            this->m_GuiLayer->End();

            this->m_Window->OnUpdate();
        }
    }

    void EmberApp::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCloseEvent));

        // Propagate events through the LayerStack from  first Layer to last Layer based on the order of insertion.
        for (auto it = this->LayerStack.End(); it != this->LayerStack.Begin(); )
        {
            // Propagate events through LayerStack.
            // Decrement the pointer first, then dereference. Otherwise faulty logic as we cannot dereference LayerStack.End().
            // --it;
            (*--it)->OnEvent(event);
            if (event.isHandled())
            {
                break;
            }
        }
    }

    bool EmberApp::OnWindowCloseEvent(WindowCloseEvent& event)
    {
        this->isRunning = false;
        return true;
    }

    void  EmberApp::PushLayer(Layer* layer)
    {
        this->LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void EmberApp::PushOverlay(Layer* overlay)
    {
        this->LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }


    Window* EmberApp::GetWindow()
    {
        return m_Window;
    }
};