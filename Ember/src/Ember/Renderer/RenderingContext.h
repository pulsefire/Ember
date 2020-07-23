#ifndef EMBER_RENDERING_CONTEXT
#define EMBER_RENDERING_CONTEXT

#include "Ember/Core/Core.h"
#include "Ember/Core/Log.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

// To support multiple Graphics APIs like vulkan or DX we would create an interface RenderingContext and
// derive OpenGlContext from it and implement virtual methods in it.
// Main RenderingContext functionality is to initialise and swap buffers for now.

namespace Ember
{
    class EMBER_API RenderingContext
    {
    public:

        RenderingContext(GLFWwindow*  windowHandle);
        void Init();
        void SwapBuffers();

    private:

        GLFWwindow* m_WindowHandle;
    };
};







#endif


