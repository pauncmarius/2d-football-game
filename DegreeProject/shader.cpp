#include "shader.h"

Shader::Shader()
{
    program = new QOpenGLShaderProgram();
}

Shader::~Shader()
{
    delete program;
}

void Shader::addShaderFromSourceCode(QOpenGLShader::ShaderType type, const char *source)
{
    program->addShaderFromSourceCode(type, source);
}

void Shader::link()
{
    program->link();
}

void Shader::bind()
{
    program->bind();
}

void Shader::release()
{
    program->release();
}
