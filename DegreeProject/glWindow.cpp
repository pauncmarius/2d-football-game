#include "glWindow.h"
#include <QOpenGLShaderProgram>
#include <QTimer>

GLWindow::GLWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    // Set window flags to prevent resizing
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window);

    // Create a timer to update the animation and physics
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLWindow::updateAnimation);
    timer->start(16); // Approximately 60 FPS
}

GLWindow::~GLWindow(){}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();  // Initialize OpenGL functions

    // Initialize the background renderer
    backgroundRenderer.initialize("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/bg1.jpg");

    // Initialize the ball with texture paths for the animation frames
    std::vector<QString> texturePaths = {
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball1.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball2.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball3.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball4.png"
    };
    ball.initialize(texturePaths);

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
    ball.render();  // Render the ball
}

void GLWindow::updateAnimation()
{
    ball.updatePhysics();
    if (ball.isJumping()) {
        ball.updateAnimationFrame();
    }
    update(); // Request a repaint to update the animation and physics
}
