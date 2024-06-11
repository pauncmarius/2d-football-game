#ifndef SHADOW_H
#define SHADOW_H

#include <QOpenGLFunctions_3_3_Core>
#include "shader.h"
#include <QMatrix4x4>

// Clasa Shadow derivată din QOpenGLFunctions_3_3_Core pentru a folosi funcțiile OpenGL
class Shadow : protected QOpenGLFunctions_3_3_Core
{
public:
    Shadow();
    ~Shadow();
    void init(); // Inițializează resursele necesare pentru desenarea umbrelor
    void render(const QMatrix4x4 &projection, float x, float y, float scale, float transparency); // Randează umbra
    void cleanup(); // Curăță resursele alocate

private:
    GLuint VAO, VBO, EBO; // ID-urile pentru Vertex Array Object, Vertex Buffer Object și Element Buffer Object
    Shader shader; // Obiectul shader pentru gestionarea shader-ului
    void setupShaders(); // Configurează și compilează shader-ele
    void setupBuffers(); // Configurează și inițializează buffer-ele
};

#endif // SHADOW_H
