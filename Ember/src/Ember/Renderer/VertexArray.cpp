#include "Ember/Renderer/VertexArray.h"
#include "Ember/Renderer/Renderer.h"

namespace Ember
{    
    static GLenum ShaderToGLBaseDataType(ShaderDataType& Type)
    {
        switch (Type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Bool:   return GL_BOOL;
        }

        ER_CORE_ASSERT(false, "Unsupported Shader Data Type!");
        return 0;
    };


    VertexArray* VertexArray::Create()
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
                return new OpenGLVertexArray();
            }
            // Example: Validate this case if  were compiling on Windows!
            #if ER_PLATFORM_WINDOWS
                    case RendererAPI::Direct3D: return new Direct3DVertexBuffer(vertices, size);
            #endif
        }
        ER_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    };


////////// OpenGL VertexArray Impl //////////

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_VertexArrayID);
    };
    
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_VertexArrayID);
    };

    void OpenGLVertexArray::Bind()
    {
        glBindVertexArray(m_VertexArrayID);
    };

    void OpenGLVertexArray::Unbind()
    {
        glBindVertexArray(0);
    };

    void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer)
    {
        ER_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size() != 0, "No Buffer Layout Specified!");

        glBindVertexArray(m_VertexArrayID);
        vertexBuffer->Bind();
        BufferLayout& bufferLayout = vertexBuffer->GetLayout();

        unsigned int idx = 0; 
        for (BufferElement& element : bufferLayout)
        {
            glEnableVertexAttribArray(idx);
            glVertexAttribPointer(idx, element.GetComponentCount(), ShaderToGLBaseDataType(element.Type), (element.Normalised ? GL_TRUE : GL_FALSE), bufferLayout.GetStride(), (const void*)element.Offset);
            idx++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    };

    void OpenGLVertexArray::AddIndexBuffer(IndexBuffer* indexBuffer)
    {
        glBindVertexArray(m_VertexArrayID);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
    };


};