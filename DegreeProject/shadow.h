#ifndef SHADOW_H
#define SHADOW_H

#include <QOpenGLFunctions_3_3_Core>
#include "shader.h"
#include <QMatrix4x4>

class Shadow : protected QOpenGLFunctions_3_3_Core
{
public:
    Shadow();
    ~Shadow();
    void init();
    void render(const QMatrix4x4 &projection, float x, float y, float scale, float transparency);
    void cleanup();

private:
    GLuint VAO, VBO, EBO;
    Shader shader;
    void setupShaders();
    void setupBuffers();
};

#endif // SHADOW_H
