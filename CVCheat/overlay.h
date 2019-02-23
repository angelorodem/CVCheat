#ifndef OVERLAY_H
#define OVERLAY_H

#include "includes.h"

class Overlay : public QWidget
{
    Q_OBJECT
private slots:
    void tick();
private:

public:
    Overlay();
    QPoint top = QPoint(0,0);
    QPoint bot = QPoint(0,0);
    QPoint ammo = QPoint(0,0);

    QColor colorA;
    QColor colorB;
    QColor colorC;
    QColor colorD;

    void paintEvent(QPaintEvent *e);

};

#endif // OVERLAY_H
