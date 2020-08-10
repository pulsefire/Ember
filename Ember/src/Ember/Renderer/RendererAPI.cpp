#include "Ember/Renderer/RendererAPI.h"


namespace Ember
{

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    void OpenGLRendererAPI::SetClearColor(const vec4& colour)
    {
        glClearColor(colour[0], colour[1], colour[2], colour[3]);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(VertexArray* vertexArray)
    {
        unsigned int count = vertexArray->GetIndexBuffers()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }

    void OpenGLRendererAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        glViewport(x, y, width, height);
    }


};