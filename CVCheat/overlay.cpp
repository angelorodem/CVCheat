#include "overlay.h"

void Overlay::tick()
{
    update();
    QTimer::singleShot(1,this,SLOT(tick()));
}

Overlay::Overlay()
{
    setWindowFlags(Qt::WindowTransparentForInput | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    //setAttribute(Qt::WA_PaintOnScreen);

    tick();
}

void Overlay::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);

    p.setPen(Qt::blue);
    p.drawRect(QRect(top,bot));

    p.setPen(Qt::red);
    p.drawLine(top.rx()-10,top.ry(),top.rx()+10,top.ry());
    p.drawLine(top.rx(),top.ry()-10,top.rx(),top.ry()+10);

    p.drawLine(bot.rx()-10,bot.ry(),bot.rx()+10,bot.ry());
    p.drawLine(bot.rx(),bot.ry()-10,bot.rx(),bot.ry()+10);


}
