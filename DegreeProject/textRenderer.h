#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QPainter>

class TextRenderer : public QWidget
{
    Q_OBJECT

public:
    explicit TextRenderer(QWidget *parent = nullptr);

    void showText(const QString &text, int duration);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString currentText;
    QTimer textTimer;
};

#endif // TEXTRENDERER_H
