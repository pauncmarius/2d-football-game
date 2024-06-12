#ifndef BALL_H
#define BALL_H

#include <QOpenGLFunctions_3_3_Core>
#include "shader.h"
#include "texture.h"
#include <QMatrix4x4>
#include <vector>

// Enum pentru stările mingii
enum BallState {
    Stopped,
    Moving
};

// Clasa Ball derivată din QOpenGLFunctions_3_3_Core pentru a folosi funcțiile OpenGL
class Ball : protected QOpenGLFunctions_3_3_Core {
public:

    float position[2]; // Poziția mingii pe axele x și y
    float velocity[2]; // Viteza mingii pe axele x și y
    float radius; // Raza mingii

    BallState state; // Starea curentă a mingii

    Ball();
    ~Ball();

    void init(const std::vector<QString> &texturePaths); // Inițializează mingea cu texturi
    void render(); // Desenează mingea
    void setProjectionMatrix(const QMatrix4x4 &projection); // Setează matricea de proiecție
    void updateSpawningAnimation(); // Actualizează animația de spawn
    void updateAnimationFrame(); // Actualizează cadrul animației
    QPointF getPosition() const; // Obține poziția mingii
    BallState getState() const; // Obține starea curentă a mingii
    QPointF getVelocity() const; // Obține viteza mingii
    void setVelocity(float vx, float vy); // Setează viteza mingii
    void updatePosition(); // Actualizează poziția mingii
    void setTransparency(float alpha); // Setează transparența mingii
    void setPosition(float x, float y); // Setează poziția mingii

private:
    GLuint VAO, VBO, EBO; // ID-urile pentru Vertex Array Object, Vertex Buffer Object și Element Buffer Object
    Shader shader; // Obiectul shader pentru gestionarea shader-elor
    std::vector<std::unique_ptr<Texture>> textures; // Texturile pentru animație

    QMatrix4x4 projectionMatrix; // Matricea de proiecție

    int currentFrame; // Cadrul curent al animației
    int numFrames; // Numărul de cadre ale animației
    int frameCounter; // Contorul cadrelor

    void setupShaders(); // Configurează și compilează shader-ele
    void setupBuffers(); // Configurează și inițializează buffer-ele
};

#endif // BALL_H
