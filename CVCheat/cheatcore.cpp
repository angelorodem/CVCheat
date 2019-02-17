#include "cheatcore.h"

void CheatCore::reload()
{
    SendKey(XK_space,0);
    if(end){
        return;
    }
    QTimer::singleShot(50,this,SLOT(reload()));
}

CheatCore::CheatCore()
{
    if((display = XOpenDisplay(NULL)) == NULL) {
        std::cout << "can not access display server!" << std::endl;
        return;
    }

    root = DefaultRootWindow(display);
    screen = QGuiApplication::primaryScreen();

    Screen* pscr = DefaultScreenOfDisplay( display );

    this->displayX = pscr->width;
    this->displayY = pscr->height;

    //XCloseDisplay( pdsp );

}

void CheatCore::setup(Overlay *t_over)
{
    over.top = t_over->top;
    over.bot = t_over->bot;
    over.setFixedSize(screen->availableSize());
    over.show();

    top = t_over->mapToGlobal(t_over->top);
    bot = t_over->mapToGlobal(t_over->bot);
}

void CheatCore::start()
{

    long frameCounter = 0;

    std::time_t timeBegin = std::time(0);
    int tick = 0;

    // Setup SimpleBlobDetector parameters.
    cv::SimpleBlobDetector::Params params;

    // Change thresholds
    params.minThreshold = 0;
    params.maxThreshold = 255;

    // Filter by Area.
    params.filterByArea = true;
    params.minArea = 5;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1f;

    // Filter by Convexity
    //params.filterByConvexity = true;
    //params.minConvexity = 0.87f;

    // Filter by Inertia
    //params.filterByInertia = true;
    //params.minInertiaRatio = 0.01f;

    std::vector<std::pair<QRect,int>> last_clicks;
    unsigned timr = 0;
    reload();

    while (true) {

        QImage inImage = screen->grabWindow(0,top.rx(),top.ry(),
                                            bot.rx()-top.rx(),bot.ry()-top.ry()).toImage();


        cv::Mat  mat( inImage.height(), inImage.width(),
                      CV_8UC4,
                      const_cast<uchar*>(inImage.bits()),
                      static_cast<size_t>(inImage.bytesPerLine())
                      );

        cv::Mat gray;
        cv::cvtColor(mat,gray,cv::COLOR_BGR2GRAY);
        cv::threshold(gray,gray,50,255,cv::THRESH_BINARY_INV);

        cv::dilate(gray,gray, cv::Mat());
        cv::erode(gray,gray, cv::Mat());

        std::vector<cv::KeyPoint> kp;

        cv::Ptr<cv::SimpleBlobDetector> bd = cv::SimpleBlobDetector::create(params);
        bd->detect( gray, kp );
        cv::drawKeypoints(gray, kp, gray, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        unsigned x,y;
        for (unsigned i = 0;i < kp.size();++i) {
            x = kp[i].pt.x + top.rx();
            y = kp[i].pt.y + top.ry();

            for (unsigned lc = 0;lc < last_clicks.size();++lc) {
                if(std::get<0>(last_clicks[lc]).contains(x,y)){
                    goto already_dead;
                }
            }

            last_clicks.push_back(std::make_pair(QRect(x-3,y-3,x+3,y+3),10));
            //qDebug() << "added one " << x << " " << y;
            move_mouse(x,y);
            mouse_click();
            mouse_click();
already_dead:
            if (std::get<1>(last_clicks.back()) < 0) {
                // qDebug() << "cleared one " << std::get<0>(last_clicks.back());
                last_clicks.pop_back();
            }
        }
        for (unsigned i = 0;i < last_clicks.size();++i) {
            std::get<1>(last_clicks[i]) -= 1;
        }

        cv::imshow("wow", gray);

        frameCounter++;


        if(27 == cv::waitKey(10)){
            break;
        }

        std::time_t timeNow = std::time(0) - timeBegin;

        if (timeNow - tick >= 1)
        {
            tick++;
            timr++;
            if (timr > 30) {
                break;
            }
            std::cout << "Frames per second: " << frameCounter << std::endl;
            frameCounter = 0;
        }
    }
    end = true;
}

void CheatCore::mouse_click(unsigned int button, int times)
{
    do{
        XTestFakeButtonEvent(display, button, true, CurrentTime);
        XFlush(display);

        XTestFakeButtonEvent(display, button, false, CurrentTime);
        XFlush(display);
        times--;
    }while(times > 0);
}

void CheatCore::move_mouse(unsigned x, unsigned y)
{
    if(!display){
        return;
    }

    XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
    XFlush(display);

    XEvent event;
    memset(&event, 0, sizeof (event));
}

void CheatCore::move_mouse(QPoint pos)
{
    if(!display){
        return;
    }

    XWarpPointer(display, None, root, 0, 0, 0, 0, pos.rx(), pos.ry());
    XFlush(display);

    XEvent event;
    memset(&event, 0, sizeof (event));
}

void CheatCore::SendKey(KeySym keysym, KeySym modsym){
    KeyCode keycode = 0, modcode = 0;
    keycode = XKeysymToKeycode (display, keysym);
    if (keycode == 0) return;
    XTestGrabControl (display, True);
    /* Generate modkey press */
    if (modsym != 0) {
        modcode = XKeysymToKeycode(display, modsym);
        XTestFakeKeyEvent (display, modcode, True, 0);
    }
    /* Generate regular key press and release */
    XTestFakeKeyEvent (display, keycode, True, 0);
    XTestFakeKeyEvent (display, keycode, False, 0);

    /* Generate modkey release */
    if (modsym != 0)
        XTestFakeKeyEvent (display, modcode, False, 0);

    XSync (display, False);
    XTestGrabControl (display, False);
}
