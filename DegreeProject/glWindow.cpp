#include "glWindow.h"
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

GLWindow::GLWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    // Set window flags to prevent resizing
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window);
}

GLWindow::~GLWindow(){}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();  // Initialize OpenGL functions

    // Initialize the background renderer
    backgroundRenderer.initialize("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/bg1.jpg");
    ball.initialize("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball1.png");  // Initialize the ball with texture

    // Set the initial projection matrix
    QMatrix4x4 projection;
    projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    ball.setProjectionMatrix(projection);
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // Adjust the projection matrix to maintain the aspect ratio
    QMatrix4x4 projection;
    float aspect = float(w) / float(h);
    if (aspect >= 1.0f) {
        projection.ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    } else {
        projection.ortho(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect, -1.0f, 1.0f);
    }
    ball.setProjectionMatrix(projection);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the background
    backgroundRenderer.render();
    // Render the ball
    ball.render();
}
