#include "glWindow.h"
#include <QOpenGLShaderProgram>

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

}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the background
    backgroundRenderer.render();
    ball.render();  // Render the ball

}
