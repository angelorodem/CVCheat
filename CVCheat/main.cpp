#include <QApplication>
#include <QScreen>
#include <ctime>
#include "mwindow.h"
#include "cheatcore.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

int main(int argc,char* argv[]){
    QApplication app(argc,argv);

    MWindow w;
    w.show();


    return app.exec();
}
