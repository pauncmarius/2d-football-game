#ifndef BALL_H
#define BALL_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <vector>

enum BallState {
    Stopped,
    Moving
};

class Ball : protected QOpenGLFunctions_3_3_Core {
public:
    Ball();
    ~Ball();
    void init(const std::vector<QString> &texturePaths);
    void render();
    void setProjectionMatrix(const QMatrix4x4 &projection);
    void updatePhysics();
    void updateAnimationFrame();
    QPointF getPosition() const;
    BallState getState() const;

private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    std::vector<QOpenGLTexture*> textures;

    float position[2];
    float velocity[2];
    float acceleration[2];
    float radius;
    float dampingFactor;

    QMatrix4x4 projectionMatrix;

    int currentFrame;
    int numFrames;
    int frameCounter;

    BallState state;

    void setupShaders();
    void setupBuffers();
};

#endif // BALL_H
