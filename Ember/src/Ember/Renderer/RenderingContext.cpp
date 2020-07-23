
#include "Ember/Renderer/RenderingContext.h"

namespace Ember
{

    RenderingContext::RenderingContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {

    }

    void RenderingContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        gladLoadGL();

        ER_CORE_INF("OpenGL Renderer: {0} {1}", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
    }   


    void RenderingContext::SwapBuffers()
    { 
        glfwSwapBuffers(m_WindowHandle);
    }

    



};