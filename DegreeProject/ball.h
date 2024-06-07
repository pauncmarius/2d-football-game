#ifndef BALL_H
#define BALL_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>

class Ball : protected QOpenGLFunctions_3_3_Core {
public:
    Ball();
    ~Ball();
    void initialize(const QString &texturePath);
    void render();
    void setProjectionMatrix(const QMatrix4x4 &projection);

private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    QOpenGLTexture *texture;
    float position[2];
    float radius;
    QMatrix4x4 projectionMatrix;

    void setupShaders();
    void setupBuffers();
};

#endif // BALL_H
