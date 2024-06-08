#include "glWindow.h"
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QKeyEvent>

GLWindow::GLWindow(QWidget *parent) : QOpenGLWidget(parent), moveLeft(false), moveRight(false), jump(false)
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
    std::vector<QString> ballTexturePaths = {
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball1.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball2.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball3.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball4.png"
    };
    ball.initialize(ballTexturePaths);

    // Initialize the player with texture paths for the idle, move left, move right, jump up, and fall down animations
    std::map<PlayerState, std::vector<QString>> playerTexturePaths = {
        {Idle, {
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_000.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_001.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_002.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_003.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_004.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_005.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_006.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_007.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_008.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_009.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_010.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_011.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_012.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_013.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_014.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_015.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_016.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Idle/Idle_017.png"
        }},
        {MoveLeft, {
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_000.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_001.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_002.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_003.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_004.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_005.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_006.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_007.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_008.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Backward/Move Backward_009.png"
        }},
        {MoveRight, {
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_000.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_001.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_002.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_003.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_004.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_005.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_006.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_007.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_008.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Move Forward/Move Forward_009.png"
        }},
        {JumpUp, {
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Jump/Jump_000.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Jump/Jump_001.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Jump/Jump_002.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Jump/Jump_003.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Jump/Jump_004.png"
        }},
        {FallDown, {
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Fall/Falling Down_000.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Fall/Falling Down_001.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Fall/Falling Down_002.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Fall/Falling Down_003.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Fall/Falling Down_004.png"
        }}
    };

    player.initialize(playerTexturePaths);
    // Set the scale for the player
    player.setScale(0.45f, 0.25f);

    // Set the initial projection matrix
    QMatrix4x4 projection;
    projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    ball.setProjectionMatrix(projection);
    player.setProjectionMatrix(projection);
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
    player.setProjectionMatrix(projection);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the background
    backgroundRenderer.render();
    // Render the ball
    ball.render();
    // Render the player
    player.render();
}

void GLWindow::updateAnimation()
{
    ball.updatePhysics();
    if (ball.isJumping()) {
        ball.updateAnimationFrame();
    }

    if (jump) {
        player.jump();
        if (moveLeft) {
            player.move(-0.02f);
        } else if (moveRight) {
            player.move(0.02f);
        }
    } else {
        if (moveLeft) {
            player.setState(MoveLeft);
            player.move(-0.02f);
        } else if (moveRight) {
            player.setState(MoveRight);
            player.move(0.02f);
        } else {
            player.setState(Idle);
        }
    }

    player.updateAnimationFrame();
    update(); // Request a repaint to update the animation and physics
}

void GLWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_A:
            moveLeft = true;
            break;
        case Qt::Key_D:
            moveRight = true;
            break;
        case Qt::Key_W:
            jump = true;
            break;
        default:
            QOpenGLWidget::keyPressEvent(event);
    }
}

void GLWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_A:
            moveLeft = false;
            break;
        case Qt::Key_D:
            moveRight = false;
            break;
        case Qt::Key_W:
            jump = false;
            break;
        default:
            QOpenGLWidget::keyReleaseEvent(event);
    }
}
