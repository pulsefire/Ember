#ifndef EMBER_RENDERER_API
#define EMBER_RENDERER_API

#include "Ember/Renderer/RenderCommand.h"
#include "Ember/Renderer/VertexArray.h"

namespace Ember
{

    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();
        static void Submit(VertexArray* vertexArray);

    public:
        inline static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetCurrentAPI(); }; 

    private:


    };
};

#endif