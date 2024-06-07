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
    void initialize(const std::vector<QString> &texturePaths);
    void render();
    void setProjectionMatrix(const QMatrix4x4 &projection);
    void updateAnimationFrame();

private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    std::vector<QOpenGLTexture*> textures;
    float position[2];
    float radius;
    QMatrix4x4 projectionMatrix;
    int currentFrame;
    int numFrames;
    int frameCounter;

    void setupShaders();
    void setupBuffers();
};

#endif // BALL_H
