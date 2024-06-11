#include "glWindow.h"
#include <QTimer>
#include <QKeyEvent>

GLWindow::GLWindow(QWidget *parent) : QOpenGLWidget(parent), moveLeft(false), moveRight(false), jump(false), kick(false), isSpawningAnimationDone(false)
{
    // Setează flag-urile ferestrei pentru a preveni redimensionarea
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Window);

    // Timer pentru actualizarea animației și fizicii
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GLWindow::updateAnimation);
    timer->start(16); // Approximately 60 FPS
}

GLWindow::~GLWindow(){}

void GLWindow::initializeGL()
{
    // Inițializează funcțiile OpenGL
    initializeOpenGLFunctions();

    // Inițializează renderer-ul de fundal
    backgroundRenderer.init("C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/bg1.jpg");

    // Setează zonele de gol
    goalZoneLeft = QRectF(-1.8f, -0.4f, 0.3f, 0.7f);
    goalZoneRight = QRectF(1.455f, -0.4f, 0.3f, 0.7f);

    // Inițializează texturile pentru minge
    std::vector<QString> ballTexturePaths = {
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball1.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball2.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball3.png",
        "C:/Users/paunm/Documents/github/2d-football-game/DegreeProject/resources/ball4.png"
    };
    ball.init(ballTexturePaths);

    // Inițializează texturile pentru jucător
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
//    debugRectangle.init();
//    debugRectangle.setColor(QColor(255, 0, 0, 128)); // Semi-transparent red

    ballShadow.init();
    playerShadow.init();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // Ajustează matricea de proiecție pentru a obține raportul de aspect dorit
    float aspect = float(w) / float(h);
    projection.ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

    ball.setProjectionMatrix(projection);
    player.setProjectionMatrix(projection);
//    debugRectangle.setProjectionMatrix(projection);
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenează fundalul
    backgroundRenderer.render();

//    // Update and render the debug rectangle
//    QRectF playerBoundingBox = player.getBoundingBox();
//    debugRectangle.setRectangle(playerBoundingBox);
//    debugRectangle.render();

    QMatrix4x4 projectionTemp;
    projectionTemp.ortho(-1.777f, 1.777f, -1.0f, 1.0f, -1.0f, 1.0f);

    QMatrix4x4 scalingMatrix;
    // Ajustează factorul de scalare pe axa y pentru a aplatiza cercul
    scalingMatrix.scale(1.0f, 0.3f);
    projectionTemp = projectionTemp * scalingMatrix;

    // Desenează umbra mingii
    QPointF ballPosition = ball.getPosition();
    float ballShadowScale = 0.060f + (ballPosition.y() * 0.05f);
    float ballShadowTransparency = 0.2f - ballPosition.y();
    ballShadow.render(projectionTemp, ballPosition.x(), -1.1f, ballShadowScale, ballShadowTransparency);

    // Desenează umbra jucătorului
    QPointF playerPosition = player.getPosition();
    float playerShadowScale = 0.035f + (0.05f - playerPosition.y() * 0.05f);
    float playerShadowTransparency = 0.2f - playerPosition.y();
    playerShadow.render(projectionTemp, playerPosition.x(), -1.1f, playerShadowScale, playerShadowTransparency);

    // Desenează mingea
    ball.render();
    // Desenează jucătorul
    player.render();
}

void GLWindow::updateAnimation()
{
    // ball
    if (!isSpawningAnimationDone) {
        ball.updateSpawningAnimation();
        if (ball.getState() == Moving) {
            ball.updateAnimationFrame();
        }
        if (ball.getState() == Stopped) {
            isSpawningAnimationDone = true;
        }
    } else {
        ball.updatePosition();
        if (ball.getState() == Moving) {
            ball.updateAnimationFrame();
        }
        //
    }

    // player
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

    // Creează bounding box-uri pentru detectarea coliziunilor
    QRectF playerBoundingBox = player.getBoundingBox();
    QRectF ballBoundingBox(ball.getPosition().x() - ball.radius, ball.getPosition().y() - ball.radius, ball.radius * 2, ball.radius * 2);

    // Detectarea coliziunilor între jucător și minge
    if (playerBoundingBox.intersects(ballBoundingBox)) {
        QPointF playerVelocity = (moveLeft ? QPointF(-0.02f, 0) : moveRight ? QPointF(0.02f, 0) : QPointF(0.02, 0));
        ball.setVelocity(playerVelocity.x(), ball.getVelocity().y()); // adjust the scaling factor as needed
    }

    // Zona de poarta
    if (goalZoneLeft.contains(player.getPosition()) || goalZoneRight.contains(player.getPosition())) {
        player.setTransparency(0.8f);
    } else {
        player.setTransparency(1.0f);
    }
    if (goalZoneLeft.contains(ball.getPosition()) || goalZoneRight.contains(ball.getPosition())) {
        ball.setTransparency(0.8f);
    } else {
        ball.setTransparency(1.0f);
    }

    // Limitele ferestrei pentru jucători
    QPointF playerPos = player.getPosition();
    if (playerPos.x() < -1.7f) {
        player.setPosition(-1.7f, playerPos.y());
    } else if (playerPos.x() > 1.7f) {
        player.setPosition(1.7f, playerPos.y());
    }
    QPointF ballPos = ball.getPosition();
    if (ballPos.x() < -1.7f) {
        ball.setPosition(-1.7f, ballPos.y());
    } else if (ballPos.x() > 1.7f) {
        ball.setPosition(1.7f, ballPos.y());
    }

    player.updateAnimationFrame();

    // Solicită redesenarea
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
