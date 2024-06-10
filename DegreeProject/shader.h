#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QString>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

class Shader : protected QOpenGLFunctions_3_3_Core
{
public:
    Shader();
    ~Shader();

    void addShaderFromSourceCode(GLenum shaderType, const char *source);
    void init();
    void link();
    void bind();
    void unbind();

    void setUniformValue(const char *name, int value);
    void setUniformValue(const char *name, float value);
    void setUniformValue(const char *name, const QVector2D &value);
    void setUniformValue(const char *name, const QVector3D &value);
    void setUniformValue(const char *name, const QVector4D &value);
    void setUniformValue(const char *name, const QMatrix4x4 &value);

private:
    GLuint program;
    GLuint vertexShader;
    GLuint fragmentShader;

    void checkCompileErrors(GLuint shader, const QString &type);
    void checkLinkErrors(GLuint program);
};

#endif // SHADER_H
