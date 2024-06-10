#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_3_3_Core>

class Shader : protected QOpenGLFunctions_3_3_Core
{
public:
    Shader();
    ~Shader();

    void addShaderFromSourceCode(GLenum shaderType, const char *source);
    void initialize();
    void link();
    void bind();
    void unbind();

private:
    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;

    void checkCompileErrors(GLuint shader, const QString &type);
    void checkLinkErrors(GLuint program);
};

#endif // SHADER_H
