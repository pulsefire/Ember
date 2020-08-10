#ifndef EMBER_WINDOW
#define EMBER_WINDOW

#include "Ember/Core/Core.h"
#include "Ember/Event/ApplicationEvent.h"
#include "Ember/Event/KeyEvent.h"
#include "Ember/Event/MouseEvent.h"

#include "Ember/Renderer/RenderingContext.h"

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

            WindowData(int w = 800, int h = 600, std::string t = "Ember Engine")
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

        GLFWwindow* GetNativeWindow();
        int GetWidth();
        int GetHeight();

        static bool glfwInitialised;

    private:
        WindowData WinData;
        GLFWwindow* m_Buffer;
        RenderingContext* m_Context;
    };
};




#endif