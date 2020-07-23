#ifndef EMBER_SHADER
#define EMBER_SHADER

#include "Ember/Core/Log.h"
#include "Ember/Renderer/Renderer.h"

#include <string>
#include <vector>


namespace Ember
{

    class Shader
    {
    public:
        Shader() {};
        virtual ~Shader() {};

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };



    class OpenGLShader : public Shader
    {
    public:

        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();

        virtual void Bind() override;
        virtual void Unbind() override;

    private:
        unsigned int m_ShaderID;
    };
};




#endif