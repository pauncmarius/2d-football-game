#ifndef DEBUGRECTANGLE_H
#define DEBUGRECTANGLE_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QColor>
#include <QRectF>
#include <QMatrix4x4>

class DebugRectangle : protected QOpenGLFunctions_3_3_Core
{
public:
    DebugRectangle();
    ~DebugRectangle();

    void initialize();
    void setRectangle(const QRectF &rect);
    void setColor(const QColor &color);
    void setProjectionMatrix(const QMatrix4x4 &projection);
    void render();

private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    QMatrix4x4 projectionMatrix;
    QColor color;
    QRectF rectangle;

    void setupShaders();
    void setupBuffers();
};

#endif // DEBUGRECTANGLE_H