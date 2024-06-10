#include "glWindow.h"
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QKeyEvent>

GLWindow::GLWindow(QWidget *parent) : QOpenGLWidget(parent), moveLeft(false), moveRight(false), jump(false), kick(false)
{
    // window flags to prevent resizing
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window);

    // timer to update the animation and physics
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLWindow::updateAnimation);
    timer->start(16); // Approximately 60 FPS
}

GLWindow::~GLWindow(){}

void GLWindow::initializeGL()
{
    // init OpenGL functions
    initializeOpenGLFunctions();

    backgroundRenderer.init("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/bg1.jpg");

    goalZoneLeft = QRectF(-1.8f, -0.4f, 0.3f, 0.7f);
    goalZoneRight = QRectF(1.455f, -0.4f, 0.3f, 0.7f);

    std::vector<QString> ballTexturePaths = {
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball1.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball2.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball3.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball4.png"
    };
    ball.init(ballTexturePaths);

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
        }},
        {Kick, {
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Kick/Kick_000.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Kick/Kick_001.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Kick/Kick_002.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Kick/Kick_003.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Kick/Kick_004.png",
            "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/characterBrazil/Kick/Kick_005.png"
        }}
    };

    player.init(playerTexturePaths);
    player.setScale(0.45f, 0.25f);
    // ex for debug rect
    debugRectangle.init();
    debugRectangle.setColor(QColor(255, 0, 0, 128)); // Semi-transparent red

    ballShadow.init();
    playerShadow.init();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // adjust the projection matrix to maintain the aspect ratio
    float aspect = float(w) / float(h);
    projection.ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

    ball.setProjectionMatrix(projection);
    player.setProjectionMatrix(projection);
    debugRectangle.setProjectionMatrix(projection);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    backgroundRenderer.render();

    // Update and render the debug rectangle
    QRectF playerBoundingBox = player.getBoundingBox();
    debugRectangle.setRectangle(playerBoundingBox);
    debugRectangle.render();

    QMatrix4x4 projectionTemp;
    projectionTemp.ortho(-1.777f, 1.777f, -1.0f, 1.0f, -1.0f, 1.0f);

    QMatrix4x4 scalingMatrix;
    scalingMatrix.scale(1.0f, 0.3f); // adjust the y-scale factor to squash the circle
    projectionTemp = projectionTemp * scalingMatrix;

    // render the ball shadow
    QPointF ballPosition = ball.getPosition();
    float ballShadowScale = 0.060f + (ballPosition.y() * 0.05f);
    float ballShadowTransparency = 0.2f - ballPosition.y();
    ballShadow.render(projectionTemp, ballPosition.x(), -1.1f, ballShadowScale, ballShadowTransparency);

    // render the player shadow
    QPointF playerPosition = player.getPosition();
    float playerShadowScale = 0.035f + (0.05f - playerPosition.y() * 0.05f);
    float playerShadowTransparency = 0.2f - playerPosition.y();
    playerShadow.render(projectionTemp, playerPosition.x(), -1.1f, playerShadowScale, playerShadowTransparency);

    ball.render();
    player.render();
}

void GLWindow::updateAnimation()
{
    ball.updatePhysics();
    if (ball.getState() == Moving) {
        ball.updateAnimationFrame();
    }

    if (kick) {
        player.kick();
        if (jump) {
            player.jump();
        }
        if (moveLeft) {
            player.move(-0.01f);
        } else if (moveRight) {
            player.move(0.01f);
        }
    } else if (jump && !goalZoneLeft.contains(player.getPosition()) && !goalZoneRight.contains(player.getPosition())) {
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

    // Update bounding boxes for collision detection
    QRectF playerBoundingBox = player.getBoundingBox();
    QRectF ballBoundingBox(ball.getPosition().x() - ball.radius, ball.getPosition().y() - ball.radius, ball.radius * 2, ball.radius * 2);
    // collision detection between player and ball
    if (playerBoundingBox.intersects(ballBoundingBox)) {
        QPointF playerVelocity = (moveLeft ? QPointF(-0.02f, 0) : moveRight ? QPointF(0.02f, 0) : QPointF(0, 0));
        ball.setVelocity(playerVelocity.x() * 50, ball.getVelocity().y()); // adjust the scaling factor as needed
    }

    // apply damping to simulate delay until the ball stops
    if (ball.getState() == Moving && !moveLeft && !moveRight) {
        QPointF ballVelocity = ball.getVelocity();
        ball.setVelocity(ballVelocity.x() * ball.dampingFactor, ballVelocity.y());
        if (std::abs(ballVelocity.x()) < 0.001f) {
            ball.setVelocity(0, ballVelocity.y());
            ball.state = Moving;
        }
    }

    // goal zone
    if (goalZoneLeft.contains(player.getPosition()) || goalZoneRight.contains(player.getPosition())) {
        player.setTransparency(0.8f);
    } else {
        player.setTransparency(1.0f);
    }

    // window's borders for players
    QPointF playerPos = player.getPosition();
    if (playerPos.x() < -1.7f) {
        player.setPosition(-1.7f, playerPos.y());
    } else if (playerPos.x() > 1.7f) {
        player.setPosition(1.7f, playerPos.y());
    }

    player.updateAnimationFrame();

    // request repaint
    update();
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
        case Qt::Key_M:
            kick = true;
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
        case Qt::Key_M:
            kick = false;
            break;
        default:
            QOpenGLWidget::keyReleaseEvent(event);
    }
}
