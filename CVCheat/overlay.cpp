#include "overlay.h"

void Overlay::tick()
{

    update();
    QTimer::singleShot(16,this,SLOT(tick()));


}

Overlay::Overlay()
{
    srand(time(NULL));
    setWindowFlags(Qt::WindowTransparentForInput | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    //setAttribute(Qt::WA_PaintOnScreen);

    colorA.setHsv(rand() % 359,254,254);
    colorB.setHsv(rand() % 359,254,254);
    colorC.setHsv(rand() % 359,254,254);
    colorD.setHsv(rand() % 359,254,254);

    tick();
}

void Overlay::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);

    //if (color_delay > 3) {
        int h, s , v;
        colorA.getHsv(&h,&s,&v);
        colorA.setHsv(h>359?0:++h,s,v);

        colorB.getHsv(&h,&s,&v);
        colorB.setHsv(h<1?359:--h,s,v);

        colorC.getHsv(&h,&s,&v);
        colorC.setHsv(h>359?0:++h,s,v);

        colorD.getHsv(&h,&s,&v);
        colorD.setHsv(h<1?359:--h,s,v);

        color_delay = 0;
   // }

    ++color_delay;


    p.setPen(colorA);
    p.drawRect(QRect(top,bot));

    p.setPen(colorB);
    p.drawLine(top.rx()-10,top.ry(),top.rx()+10,top.ry());
    p.drawLine(top.rx(),top.ry()-10,top.rx(),top.ry()+10);


    p.setPen(colorC);
    p.drawLine(bot.rx()-10,bot.ry(),bot.rx()+10,bot.ry());
    p.drawLine(bot.rx(),bot.ry()-10,bot.rx(),bot.ry()+10);

    p.setPen(colorD);
    p.drawLine(ammo.rx()-10,ammo.ry(),ammo.rx()+10,ammo.ry());
    p.drawLine(ammo.rx(),ammo.ry()-10,ammo.rx(),ammo.ry()+10);


}
