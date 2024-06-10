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
    float dampingFactor;
    float position[2];
    float velocity[2];
    float acceleration[2];
    float radius;

    BallState state;

    Ball();
    ~Ball();
    void init(const std::vector<QString> &texturePaths);
    void render();
    void setProjectionMatrix(const QMatrix4x4 &projection);
    void updatePhysics();
    void updateAnimationFrame();
    QPointF getPosition() const;
    BallState getState() const;
    QPointF getVelocity() const;
    void setVelocity(float vx, float vy);

private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    std::vector<QOpenGLTexture*> textures;

    QMatrix4x4 projectionMatrix;

    int currentFrame;
    int numFrames;
    int frameCounter;

    void setupShaders();
    void setupBuffers();
};

#endif // BALL_H
