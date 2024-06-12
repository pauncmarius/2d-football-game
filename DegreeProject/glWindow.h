#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include "backgroundRenderer.h"
#include "ball.h"
#include "player.h"
#include "debugRectangle.h"
#include "shadow.h"

// Clasa GLWindow derivată din QOpenGLWidget și QOpenGLFunctions_3_3_Core pentru a crea și gestiona fereastra OpenGL
class GLWindow : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    explicit GLWindow(QWidget *parent = nullptr);
    ~GLWindow();

protected:
    void initializeGL() override; // Inițializează contextul OpenGL
    void resizeGL(int w, int h) override; // Reconfigurează viewport-ul când fereastra este redimensionată
    void paintGL() override; // Desenează scena
    void keyPressEvent(QKeyEvent *event) override; // Gestionează evenimentele de tastatură
    void keyReleaseEvent(QKeyEvent *event) override; // Gestionează eliberarea tastelor

private slots:
    void updateAnimation(); // Actualizează animația și fizica

private:
    BackgroundRenderer backgroundRenderer; // Renderer pentru fundal
    Ball ball; // Obiectul mingii
    Player player; // Obiectul jucătorului
    Shadow ballShadow; // Umbră pentru minge
    Shadow playerShadow; // Umbră pentru jucător

    bool moveLeft; // Bool pentru mișcarea la stânga
    bool moveRight; // Bool pentru mișcarea la dreapta
    bool jump; // Bool pentru săritură
    bool kick; // Bool pentru lovitură
    bool isSpawningAnimationDone; // Flag pentru finalizarea animației de spawn

    // Dreptunghiuri de debug
    DebugRectangle debugRectangle1;
    DebugRectangle debugRectangle2;
    DebugRectangle debugRectangle3;
    DebugRectangle debugRectangle4;

    QRectF goalZoneLeft; // Zona de poartă stânga
    QRectF goalZoneRight; // Zona de poartă dreapta
    QRectF playerBoundingBox; // Bounding box pentru jucător
    QRectF ballBoundingBox; // Bounding box pentru minge

    QMatrix4x4 projection; // Matricea de proiecție

    void resetGame();

};

#endif // GLWINDOW_H
