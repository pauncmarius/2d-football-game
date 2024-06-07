#include <QApplication>
#include <QSurfaceFormat>

#include "glWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLWindow w;
    w.resize(1280, 720);
    w.show();

    return a.exec();
}
