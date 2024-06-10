#ifndef PLAYER_H
#define PLAYER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <vector>
#include <map>

enum PlayerState {
    Idle,
    MoveLeft,
    MoveRight,
    JumpUp,
    FallDown,
    Kick
};

class Player : protected QOpenGLFunctions_3_3_Core
{
public:
    Player();
    ~Player();
    void init(const std::map<PlayerState, std::vector<QString>> &texturePaths);
    void render();
    void setProjectionMatrix(const QMatrix4x4 &projection);
    void updateAnimationFrame();
    void setScale(float widthScale, float heightScale);
    void setState(PlayerState state);
    void move(float dx);
    void jump();
    void kick();
    QPointF getPosition() const;
    void setTransparency(float alpha);
    void setPosition(float x, float y);


private:
    GLuint VAO, VBO, EBO;
    QOpenGLShaderProgram shader;
    std::map<PlayerState, std::vector<QOpenGLTexture*>> textures;
    PlayerState currentState;
    float position[2];
    float widthScale, heightScale;
    QMatrix4x4 projectionMatrix;
    int currentFrame;
    int frameCounter;
    std::map<PlayerState, int> numFrames;

    float velocityY;
    bool isJumping;

    void setupShaders();
    void setupBuffers();
};

#endif // PLAYER_H
