#include "Ember/Window.h"


namespace Ember
{

    Window::Window(const Window::WindowData& data)
    {
        this->Init(data);
    }

    Window::~Window()
    {

    }

    void Window::Init(const Window::WindowData& data)
    {
        this->WinData.width = data.width;
        this->WinData.height = data.height;
        this->WinData.title = data.title;

        if (!glfwInitialised)
        {
            glfwInitialised = true;
            glfwInit();
        }
        // Create glfw window
        this->m_Buffer = glfwCreateWindow(this->WinData.width, this->WinData.height, this->WinData.title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(this->m_Buffer);

        gladLoadGL();

        // Set WindowData as user defined data. 
        glfwSetWindowUserPointer(this->m_Buffer, &this->WinData);

        // Set glfw callbacks.

        glfwSetWindowCloseCallback(this->m_Buffer, [](GLFWwindow* window)
        {
            Window::WindowData data = *(Window::WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(this->m_Buffer, [](GLFWwindow* window, int key, int scancode, int action, int mods){

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

    }

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

    bool Window::glfwInitialised = false;
};