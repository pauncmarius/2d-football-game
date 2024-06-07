// Ball.h
#ifndef BALL_H
#define BALL_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Ball : protected QOpenGLFunctions_3_3_Core {
public:
    Ball();
    ~Ball();
    void initialize(const QString &texturePath);
    void render();

private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    QOpenGLTexture *texture;
    float position[2];
    float radius;

    void setupShaders();
    void setupBuffers();
};

#endif // BALL_H
