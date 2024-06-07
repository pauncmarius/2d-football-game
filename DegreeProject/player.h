#ifndef PLAYER_H
#define PLAYER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <vector>

class Player : protected QOpenGLFunctions_3_3_Core
{
public:
    Player();
    ~Player();
    void initialize(const std::vector<QString> &texturePaths);
    void render();
    void setProjectionMatrix(const QMatrix4x4 &projection);
    void updateAnimationFrame();
    void setScale(float widthScale, float heightScale);


private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    std::vector<QOpenGLTexture*> textures;
    float position[2];
    float widthScale, heightScale;
    QMatrix4x4 projectionMatrix;
    int currentFrame;
    int numFrames;
    int frameCounter;

    void setupShaders();
    void setupBuffers();
};

#endif // PLAYER_H
