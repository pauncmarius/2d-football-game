#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "texture.h"
#include "shader.h"

class GLWindow : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    explicit GLWindow(QWidget *parent = nullptr);
    ~GLWindow();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    Texture *texture;
    Shader *shaderProgram;
    GLuint VBO, VAO, EBO;

    void setupShaders();
};

#endif // GLWINDOW_H
