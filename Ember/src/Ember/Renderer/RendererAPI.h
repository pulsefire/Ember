#pragma once


#include "Ember/Core/Core.h"
#include "Ember/Renderer/VertexArray.h"
#include "linmath.h"


namespace Ember
{

    class RendererAPI
    {
    public:

        enum class API
        {
            None = 0, OpenGL = 1
        };

    public:
        virtual ~RendererAPI() = 0;

        virtual void SetClearColor(const vec4& colour) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(VertexArray* vertexArray) = 0;
        virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;

        static inline API GetCurrentAPI() { return s_API; };

    private:
        static API s_API;
    };



    class OpenGLRendererAPI : public RendererAPI
    {
    public:

        OpenGLRendererAPI() {};
        ~OpenGLRendererAPI() {};

        virtual void SetClearColor(const vec4& colour) override;
        virtual void Clear() override;
        virtual void DrawIndexed(VertexArray* vertexArray) override;
        virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
    };



};