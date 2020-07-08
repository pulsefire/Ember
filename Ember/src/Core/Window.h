#ifndef EMBER_WINDOW
#define EMBER_WINDOW

#include "Core/Core.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Ember
{
    class EMBER_API Window
    {
    public:
        // Pointer to function with signature void func(Event&);
        // Type alias for void (*)(Event&) EventFn;
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

        Window(const WindowData& data = WindowData());
        ~Window();

        void Init(const WindowData& data);
        void SetEventCallback(const EventFn& callback);
        void SetVSync(bool Enabled);
        void OnUpdate();
        void Shutdown();

        WindowData WinData;
        GLFWwindow* m_Buffer;

        static bool glfwInitialised;
    };
};




#endif