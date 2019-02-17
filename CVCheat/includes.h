#ifndef INCLUDES_H
#define INCLUDES_H

//Inclusion header, get rid of nasty recursive imports and better compile performance.

#include <QPixmap>
#include <QGuiApplication>
#include <QPoint>
#include <QImage>
#include <QWidget>
#include <QCursor>
#include <QScreen>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include <QApplication>
#include <QDebug>

#include <vector>
#include <tuple>
#include <ctime>

#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/features2d.hpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <unistd.h>

#endif // INCLUDES_H
