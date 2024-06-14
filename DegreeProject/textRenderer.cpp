#include "textRenderer.h"

TextRenderer::TextRenderer(QWidget *parent)
    : QWidget(parent), currentText("")
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(&textTimer, &QTimer::timeout, this, [this]() {
        currentText.clear();
        update();
    });
}

void TextRenderer::showText(const QString &text, int duration)
{
    currentText = text;
    textTimer.start(duration);
    update();
}

void TextRenderer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (!currentText.isEmpty()) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 24, QFont::Bold));
        QRect rect = this->rect();
        painter.drawText(rect, Qt::AlignCenter, currentText);
    }
}
