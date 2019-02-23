#ifndef CHEATCORE_H
#define CHEATCORE_H

#include "includes.h"
#include "overlay.h"

extern "C" {
#include <xdo.h>
}

class CheatCore :public QObject
{
    Q_OBJECT
    QScreen *screen;
private slots:
    void check_ammo();
private:
    static const unsigned LEFT_MOUSE_BUTTON = 1;
    static const unsigned RIGHT_MOUSE_BUTTON = 2;
    static const unsigned MIDDLE_MOUSE_BUTTON = 3;

    Display *display;
    Window root;
    Window w;
    XEvent event;

    QPoint top, bot, ammo;

    size_t displayX;
    size_t displayY;
    bool end = false;
    xdo_t * x ;


    Overlay over;

public:
    CheatCore();
    void start();
    void setup(Overlay* t_over);
    void mouse_click(unsigned int button = 1, int times = 1);
    void move_mouse(unsigned x, unsigned y);
    void move_mouse(QPoint pos);


    void SendKey();
};

#endif // CHEATCORE_H
