#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

private:
    Ui::Game *ui;
    QLabel *backgroundLabel;


};
#endif // GAME_H
