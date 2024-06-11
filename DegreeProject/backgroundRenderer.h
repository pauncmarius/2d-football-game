#ifndef BACKGROUNDRENDERER_H
#define BACKGROUNDRENDERER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QString>
#include "texture.h"
#include "shader.h"

// Clasa BackgroundRenderer derivată din QOpenGLFunctions_3_3_Core pentru a folosi funcțiile OpenGL
class BackgroundRenderer : protected QOpenGLFunctions_3_3_Core {
public:
    BackgroundRenderer();
    ~BackgroundRenderer();

    void init(const QString &texturePath); // Inițializează renderer-ul de fundal cu textura
    void render(); // Desenează fundalul

private:
    Texture texture; // Textura de fundal
    Shader shader; // Shader-ul pentru fundal
    GLuint VAO, VBO, EBO; // ID-urile pentru Vertex Array Object, Vertex Buffer Object și Element Buffer Object

    void setupBuffers(); // Configurează și inițializează buffer-ele
    void setupShaders(); // Configurează și compilează shader-ele
};

#endif // BACKGROUNDRENDERER_H
