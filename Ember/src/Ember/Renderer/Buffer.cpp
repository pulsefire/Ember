
#include "Ember/Renderer/Buffer.h"
#include "Ember/Renderer/Renderer.h"

// If we support multiple platforms and multiple Rendering APIs
#if ER_PLATFORM_WINDOWS
#include "Ember/Platform/Direct3D/Direct3DBuffer.h"
#endif

namespace Ember
{

    VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size) 
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::API::None:
            {
                ER_CORE_ASSERT(false, "RendererAPI::None not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
            {
                return new OpenGLVertexBuffer(vertices, size);
            }
            // Example: Validate this case if  were compiling on Windows!
            #if ER_PLATFORM_WINDOWS
                    case RendererAPI::Direct3D: return new Direct3DVertexBuffer(vertices, size);
            #endif
        }
        ER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    };

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
    {   
        glCreateBuffers(1, &m_GLVertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_GLVertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_GLVertexBufferID);
    }

    void OpenGLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_GLVertexBufferID);
    }

    void OpenGLVertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLVertexBuffer::SetLayout(const BufferLayout& Layout)
    {
        m_Layout = Layout;
    }

    BufferLayout& OpenGLVertexBuffer::GetLayout()
    {
        return m_Layout;
    }



// If its count then its elements, if its size then its bytes!
//////////////////////////////////////////////////////////////////////////////
// Vertex Buffer /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


    OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int count)
        : IndexBuffer(), m_Count(count)
    {
        glCreateBuffers(1, &m_GLIndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLIndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_GLIndexBufferID);
    }

    void OpenGLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GLIndexBufferID);
    }

    void OpenGLIndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    unsigned int OpenGLIndexBuffer::GetCount()
    {   
        return m_Count;
    }

    IndexBuffer* IndexBuffer::Create(unsigned int* vertices, unsigned int size) 
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::API::None:
            {
                ER_CORE_ASSERT(false, "RendererAPI::None not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
            {
                return new OpenGLIndexBuffer(vertices, size);
            }
        }
        ER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    };
};