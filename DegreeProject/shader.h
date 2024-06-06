#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>

class Shader
{
public:
    Shader();
    ~Shader();

    void addShaderFromSourceCode(QOpenGLShader::ShaderType type, const char *source);
    void link();
    void bind();
    void release();

private:
    QOpenGLShaderProgram *program;
};

#endif // SHADER_H
