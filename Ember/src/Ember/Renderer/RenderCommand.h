#ifndef EMBER_RENDER_COMMAND
#define EMBER_RENDER_COMMAND

#include "Ember/Renderer/RendererAPI.h"

namespace Ember
{

    class RenderCommand
    {
    public:

        static inline void DrawIndexed(VertexArray* vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

        static inline void SetClearColor(const vec4& colour)
        {
            s_RendererAPI->SetClearColor(colour);
        };

        static inline void Clear()
        {
            s_RendererAPI->Clear();
        }

        static inline void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
        {
            s_RendererAPI->SetViewport(x, y, width, height);
        }

    private:
        static RendererAPI* s_RendererAPI;
    };



};



#endif