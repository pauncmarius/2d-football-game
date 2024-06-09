#ifndef BALL_H
#define BALL_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <vector>

class Ball : protected QOpenGLFunctions_3_3_Core {
public:
    Ball();
    ~Ball();
    void initialize(const std::vector<QString> &texturePaths);
    void render();
    void setProjectionMatrix(const QMatrix4x4 &projection);
    void updatePhysics();
    bool isJumping() const;
    void updateAnimationFrame();
    QPointF getPosition() const;

private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    std::vector<QOpenGLTexture*> textures;
    float position[2];
    float velocity[2];
    float acceleration[2];
    float radius;
    QMatrix4x4 projectionMatrix;
    int currentFrame;
    int numFrames;
    int frameCounter;
    bool jumping;
    float dampingFactor;

    void setupShaders();
    void setupBuffers();
};

#endif // BALL_H
