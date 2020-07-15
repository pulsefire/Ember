#include "Ember/Core/Window.h"
#include "Ember/Core/Log.h"
#include "imgui.h"

namespace Ember
{
    bool Window::glfwInitialised = false;

    static void glfwErrorCallback(int error, const char* desc)
    {
        ER_CORE_CRT("glfw ERROR! {0} {1}", error, desc);
    }

    Window::Window(const WindowData& data)
    {
        this->Init(data);
    }

    Window::~Window()
    {
        this->Shutdown();
    }

    void Window::Init(const Window::WindowData& data)
    {
        this->WinData.width = data.width;
        this->WinData.height = data.height;
        this->WinData.title = data.title;

        if (!glfwInitialised)
        {
            glfwInitialised = true;
            int success = glfwInit();
            glfwSetErrorCallback(glfwErrorCallback);
            ER_CORE_ASSERT(success, "Unable to initialize glfw!");
        }
        // Create glfw window
        this->m_Buffer = glfwCreateWindow(this->WinData.width, this->WinData.height, this->WinData.title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(this->m_Buffer);
        // Load OpenGL
        gladLoadGL();
        // Set WindowData as user defined data. 
        glfwSetWindowUserPointer(this->m_Buffer, &this->WinData);
        this->SetVSync(true);

        // Use captureless lambdas to implement callbacks.
        glfwSetWindowCloseCallback(this->m_Buffer, [](GLFWwindow* window)
        {
            Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetWindowSizeCallback(this->m_Buffer, [](GLFWwindow* window, int width, int height)
        {
            Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        }); 

        glfwSetKeyCallback(this->m_Buffer, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressEvent event(key, 0); 
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleaseEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(this->m_Buffer, [](GLFWwindow* window, unsigned int c)
        {
            Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            KeyTypeEvent event(c);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(this->m_Buffer, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MousePressEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseReleaseEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }

        });

        glfwSetScrollCallback(this->m_Buffer, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            MouseScrollEvent event(xOffset, yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(this->m_Buffer, [](GLFWwindow* window, double xPos, double yPos)
        {
            Window::WindowData& data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            MouseMoveEvent event(xPos, yPos);
            data.EventCallback(event);
        });

    };

    void Window::SetEventCallback(const EventFn& callback)
    {
        this->WinData.EventCallback = callback;
    }

    void Window::SetVSync(bool Enabled)
    {
        if (Enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(this->m_Buffer);
    }

    void Window::Shutdown()
    {
        glfwDestroyWindow(this->m_Buffer);
    }

    GLFWwindow* Window::GetNativeWindow()
    {
        return m_Buffer;
    }

    int Window::GetWidth()
    {
        return WinData.width;
    }

    int Window::GetHeight()
    {
        return WinData.height;
    }
};