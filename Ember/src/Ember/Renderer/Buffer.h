#ifndef EMBER_RENDER_BUFFER
#define EMBER_RENDER_BUFFER

#include "Ember/Core/Core.h"
#include "Ember/Core/Log.h"

#include "glad/glad.h"

namespace Ember
{
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
    };

    static unsigned int GetShaderDataTypeSize(const ShaderDataType& Type)
    {
        switch (Type)
        {
            case ShaderDataType::None:   ER_CORE_ASSERT(false, "ShaderDataType::None not supported!"); return 0;
            case ShaderDataType::Float:  return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Int:    return 4;
            case ShaderDataType::Int2:   return 4 * 2;
            case ShaderDataType::Int3:   return 4 * 3;
            case ShaderDataType::Int4:   return 4 * 4;
            case ShaderDataType::Mat3:   return 4 * 3 * 3;
            case ShaderDataType::Mat4:   return 4 * 4 * 4;
            case ShaderDataType::Bool:   return 1;
        }

        ER_CORE_ASSERT(false, "Unsupported Shader Data Type!"); 
        return 0;
    };
    
    class BufferElement
    {
    public:
        ShaderDataType Type;
        std::string Name;
        unsigned int Size;
        int Offset;
        bool Normalised;

        BufferElement(const ShaderDataType& Type, std::string Name, bool Normalised = false)
            : Name(Name), Type(Type), Size(GetShaderDataTypeSize(Type)), Offset(0), Normalised(Normalised)
        {

        };

        int GetComponentCount()
        {
            switch (Type)
            {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Mat3:   return 9;
                case ShaderDataType::Mat4:   return 16;
                case ShaderDataType::Bool:   return 1;
            } 
        };

    };

    class BufferLayout
    {
    public:

        BufferLayout() {};

        BufferLayout(const std::initializer_list<BufferElement>& Elements)
            : m_Elements(Elements), m_Stride(0)
        {
            CalcOffsetAndStride();
        }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); };
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); };

        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        inline const unsigned int GetStride() const { return m_Stride; };
    private:

        void CalcOffsetAndStride()
        {
            int offset = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
            
        };

        std::vector<BufferElement> m_Elements;
        unsigned int m_Stride;
    };

    class VertexBuffer
    {
    public:
        VertexBuffer() {};
        virtual ~VertexBuffer() {};

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetLayout(const BufferLayout& Layout) = 0;
        virtual BufferLayout& GetLayout() = 0;

        static VertexBuffer* Create(float* vertices, unsigned int size);
    };

    class IndexBuffer
    {
    public:
        IndexBuffer() {};
        virtual ~IndexBuffer() {};
        
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual unsigned int GetCount() = 0;

        static IndexBuffer* Create(unsigned int* vertices, unsigned int size);
    };




    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, unsigned int size);
        ~OpenGLVertexBuffer();

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void SetLayout(const BufferLayout& Layout) override;
        virtual BufferLayout& GetLayout() override;

    private:
        unsigned int m_GLVertexBufferID;
        BufferLayout m_Layout;
    };




    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
        ~OpenGLIndexBuffer();

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual unsigned int GetCount() override;

    private:
        unsigned int m_GLIndexBufferID;
        unsigned int m_Count;
    };
};



#endif