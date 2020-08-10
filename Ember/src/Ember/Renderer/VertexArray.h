#ifndef EMBER_RENDERER_VERTEX_ARRAY
#define EMBER_RENDERER_VERTEX_ARRAY

#include "Ember/Core/Core.h"
#include "Ember/Renderer/Buffer.h"

namespace Ember
{

    class EMBER_API VertexArray
    {
    public:
        virtual ~VertexArray() {};

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
        virtual void AddIndexBuffer(IndexBuffer* indexBuffer) = 0;

        virtual std::vector<VertexBuffer*> GetVertexBuffers() = 0;
        virtual IndexBuffer* GetIndexBuffers() = 0;
    
        static VertexArray* Create();
    };




    class EMBER_API OpenGLVertexArray : public VertexArray
    {
    public:   
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
        virtual void AddIndexBuffer(IndexBuffer* indexBuffer) override;

        virtual inline std::vector<VertexBuffer*> GetVertexBuffers() { return m_VertexBuffers; };
        virtual inline IndexBuffer* GetIndexBuffers() { return m_IndexBuffer; };
    
    private:
        unsigned int m_VertexArrayID;
        std::vector<VertexBuffer*> m_VertexBuffers;
        IndexBuffer* m_IndexBuffer;
    };
};  




#endif