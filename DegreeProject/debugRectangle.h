#ifndef DEBUGRECTANGLE_H
#define DEBUGRECTANGLE_H

#include <QOpenGLFunctions_3_3_Core>
#include "shader.h"
#include <QColor>
#include <QRectF>
#include <QMatrix4x4>

// Clasa DebugRectangle derivată din QOpenGLFunctions_3_3_Core pentru a folosi funcțiile OpenGL
class DebugRectangle : protected QOpenGLFunctions_3_3_Core
{
public:
    DebugRectangle();
    ~DebugRectangle();

    void init(); // Inițializează resursele necesare pentru desenarea dreptunghiului
    void setRectangle(const QRectF &rect); // Setează coordonatele dreptunghiului
    void setColor(const QColor &color); // Setează culoarea dreptunghiului
    void setProjectionMatrix(const QMatrix4x4 &projection); // Setează matricea de proiecție
    void render(); // Desenează dreptunghiul

private:
    GLuint VAO, VBO, EBO; // ID-urile pentru Vertex Array Object, Vertex Buffer Object și Element Buffer Object
    Shader shader; // Obiectul shader pentru gestionarea shader-elor
    QMatrix4x4 projectionMatrix; // Matricea de proiecție
    QColor color; // Culoarea dreptunghiului
    QRectF rectangle; // Coordonatele dreptunghiului

    void setupShaders(); // Configurează și compilează shader-ele
    void setupBuffers(); // Configurează și inițializează buffer-ele
};

#endif // DEBUGRECTANGLE_H
