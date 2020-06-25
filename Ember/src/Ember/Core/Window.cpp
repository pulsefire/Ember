#include "Ember/Core/Window.h"
#include "Ember/Core/Log.h"

namespace Ember
{
    bool Window::glfwInitialised = false;
    // Returns new instance of Window.
    Window* Window::Create(const WindowData& data)
    {
        return new Window(data);
    }

    static void glfwErrorCallback(int error, const char* desc)
    {
        ER_CORE_ERR("glfw ERROR!", error, desc);
    }

    Window::Window(const Window::WindowData& data)
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

        // Set glfw callbacks.
        glfwSetWindowCloseCallback(this->m_Buffer, [](GLFWwindow* window)
        {
            Window::WindowData data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetWindowSizeCallback(this->m_Buffer, [](GLFWwindow* window, int width, int height)
        {
            Window::WindowData data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        }); 

        glfwSetKeyCallback(this->m_Buffer, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window::WindowData data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0); 
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(this->m_Buffer, [](GLFWwindow* window, int button, int action, int mods)
        {
            Window::WindowData data = *(Window::WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MousePressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }

        });

        glfwSetScrollCallback(this->m_Buffer, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            Window::WindowData data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event(xOffset, yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(this->m_Buffer, [](GLFWwindow* window, double xPos, double yPos)
        {
            Window::WindowData data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event(xPos, yPos);
            data.EventCallback(event);
        });

    };

    void Window::SetEventCallback(const EventFn& callback)
    {
        this->WinData.EventCallback = callback;
    }

    void Window::SetVSync(bool IsEnabled)
    {
        if (IsEnabled)
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
};