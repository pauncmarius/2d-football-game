#ifndef PLAYER_H
#define PLAYER_H

#include <QOpenGLFunctions_3_3_Core>
#include "shader.h"
#include "texture.h"
#include <QMatrix4x4>
#include <vector>
#include <map>
#include <memory>

// Enum pentru stările jucătorului
enum PlayerState {
    Idle,
    MoveLeft,
    MoveRight,
    JumpUp,
    FallDown,
    Kick
};

// Clasa Player derivată din QOpenGLFunctions_3_3_Core pentru a folosi funcțiile OpenGL
class Player : protected QOpenGLFunctions_3_3_Core
{
public:
    Player();
    ~Player();
    void init(const std::map<PlayerState, std::vector<QString>> &texturePaths); // Inițializează jucătorul cu texturi
    void render(); // Desenează jucătorul
    void setProjectionMatrix(const QMatrix4x4 &projection); // Setează matricea de proiecție
    void updateAnimationFrame(); // Actualizează cadrul animației
    void setScale(float widthScale, float heightScale); // Setează scala jucătorului
    void setState(PlayerState state); // Setează starea jucătorului
    void move(float dx); // Mișcă jucătorul pe axa x
    void jump(); // Face jucătorul să sară
    void kick(); // Face jucătorul să lovească
    QPointF getPosition() const; // Obține poziția jucătorului
    void setTransparency(float alpha); // Setează transparența jucătorului
    void setPosition(float x, float y); // Setează poziția jucătorului
    QRectF getBoundingBox() const; // Obține bounding box-ul jucătorului

private:
    GLuint VAO, VBO, EBO; // ID-urile pentru Vertex Array Object, Vertex Buffer Object și Element Buffer Object
    Shader shader; // Obiectul shader pentru gestionarea shader-elor
    std::map<PlayerState, std::vector<std::unique_ptr<Texture>>> textures; // Texturile pentru fiecare stare
    PlayerState currentState; // Starea curentă a jucătorului
    float position[2]; // Poziția jucătorului
    float widthScale, heightScale; // Scala jucătorului
    QMatrix4x4 projectionMatrix; // Matricea de proiecție
    int currentFrame; // Cadrul curent al animației
    int frameCounter; // Contorul cadrelor
    std::map<PlayerState, int> numFrames; // Numărul de cadre pentru fiecare stare

    float velocityY; // Viteza pe axa Y
    bool isJumping; // Bool pentru sărit

    void setupShaders(); // Configurează și compilează shader-ele
    void setupBuffers(); // Configurează și inițializează buffer-ele
};

#endif // PLAYER_H
