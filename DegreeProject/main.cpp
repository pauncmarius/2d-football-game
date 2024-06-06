#include <QApplication>
#include "glwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLWindow w;
    w.resize(800, 600);
    w.show();

    return a.exec();
}
