#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QString>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

// Clasa Shader, derivată din QOpenGLFunctions_3_3_Core pentru a utiliza funcțiile OpenGL
class Shader : protected QOpenGLFunctions_3_3_Core
{
public:
    Shader();
    ~Shader();

    void addShaderFromSourceCode(GLenum shaderType, const char *source); // Adaugă un shader din codul sursă
    void init(); // Inițializează programul shader
    void link(); // Leagă shaderele la programul OpenGL
    void bind(); // Activează programul shader
    void unbind(); // Dezactivează programul shader

    // Setează valorile uniform pentru diferite tipuri de date
    void setUniformValue(const char *name, int value);
    void setUniformValue(const char *name, float value);
    void setUniformValue(const char *name, const QVector2D &value);
    void setUniformValue(const char *name, const QVector3D &value);
    void setUniformValue(const char *name, const QVector4D &value);
    void setUniformValue(const char *name, const QMatrix4x4 &value);

private:
    GLuint program; // ID-ul programului OpenGL
    GLuint vertexShader; // ID-ul shader-ului vertex
    GLuint fragmentShader; // ID-ul shader-ului fragment

    // Verifică erorile de compilare a shader-ului
    void checkCompileErrors(GLuint shader, const QString &type);
    // Verifică erorile de legare a programului
    void checkLinkErrors(GLuint program);
};

#endif // SHADER_H
