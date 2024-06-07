#ifndef BACKGROUNDRENDERER_H
#define BACKGROUNDRENDERER_H

#include <QOpenGLFunctions_3_3_Core>
#include <QString>
#include "texture.h"
#include "shader.h"

class BackgroundRenderer : public QOpenGLFunctions_3_3_Core {
public:
    BackgroundRenderer();
    ~BackgroundRenderer();

    void initialize(const QString &texturePath);
    void render();

private:
    Texture texture;
    Shader shader;
    GLuint VAO, VBO, EBO;

    void setupBuffers();
    void setupShaders();
};

#endif // BACKGROUNDRENDERER_H
