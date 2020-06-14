#ifndef EMBER_WINDOW
#define EMBER_WINDOW

#include "Ember/Core.h"
#include "Ember/Event/ApplicationEvent.h"
#include "Ember/Event/KeyEvent.h"
#include "Ember/Event/MouseEvent.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Ember
{
    class EMBER_API Window
    {
    public:
        // Pointer to function with signature void func(Event&);
        // Type alias for void (*)(Event&)
        // typedef void (*EventFn)(Event&);
        using EventFn = std::function<void(Event&)>;

        // Struct is used here so data can be retrieved within lambdas used to implement glfw callbacks.
        struct WindowData
        {
            int width, height;
            std::string title;
            EventFn EventCallback;

            WindowData(int w = 1280, int h = 720, std::string t = "Ember Engine")
                : width(w), height(h), title(t)
            {
                
            }
        };

        Window(const WindowData& data);
        ~Window();

        void Init(const WindowData& data);
        void SetEventCallback(const EventFn& callback);
        void SetVSync(bool IsEnabled);
        void OnUpdate();
        void Shutdown();

        WindowData WinData;
        GLFWwindow* m_Buffer;
        
        static Window* Create(const WindowData& data = WindowData());
        static bool glfwInitialised;
    };
};




#endif