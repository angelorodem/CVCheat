#include "cheatcore.h"

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
    x = xdo_new(NULL);

    Window *list;
    xdo_search_t search;
    unsigned int nwindows;
    memset(&search, 0, sizeof(xdo_search_t));
    search.max_depth = -1;
    search.require = xdo_search::SEARCH_ANY;

    search.searchmask = SEARCH_CLASS | SEARCH_ONLYVISIBLE;
    search.winclass = "Chrome";

    int id = xdo_search_windows(x, &search, &list, &nwindows);
    qDebug() << nwindows;
    if(!nwindows){
        qDebug() << "Could not find that fkin window";
        return;
    }

    w = list[0];

    xdo_activate_window(x,w);
    xdo_activate_window(x,w);

}

void CheatCore::setup(Overlay *t_over)
{
    over.top = t_over->top;
    over.bot = t_over->bot;
    over.ammo = t_over->ammo;
    over.setFixedSize(screen->availableSize());
    over.show();

    top = t_over->mapToGlobal(t_over->top);
    bot = t_over->mapToGlobal(t_over->bot);
    ammo = t_over->mapToGlobal(t_over->ammo);
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
    //reload();
    check_ammo();
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
            //move_mouse(x,y);
            //mouse_click();
            //mouse_click();
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

void CheatCore::check_ammo()
{

    QImage inImage = screen->grabWindow(0,ammo.rx()-1,ammo.ry()-1,
                                        1,1).toImage();

    cv::Mat  mat( inImage.height(), inImage.width(),
                  CV_8UC4,
                  const_cast<uchar*>(inImage.bits()),
                  static_cast<size_t>(inImage.bytesPerLine())
                  );


    unsigned char color = ((uint8_t*)mat.data)[0];

    if(color > 127){//b > 128
        qDebug() << "Trying to reload, i promisse!";
        SendKey();
    }

    QTimer::singleShot(1000,this,SLOT(check_ammo()));
}

void CheatCore::SendKey(){

    xdo_activate_window(x,w);
    xdo_activate_window(x,w);
    xdo_send_keysequence_window_down(x, w, "space", 500);
    //xdo_send_keysequence_window(x, w, "space", 500);
    //xdo_send_keysequence_window(x, w, "space", 500);
    // xdo_send_keysequence_window_down(x, w, "space", 500);
    // xdo_send_keysequence_window_up(x, w, "space", 500);
    //xdo_send_keysequence_window_up(x, w, "space", 500);
    /*KeyCode keycode = 0;
    keycode = XKeysymToKeycode (display, keysym);

    //XTestGrabControl (display, True);


    XTestFakeKeyEvent (display, keycode, True, 0);
    usleep(10000000);
    XTestFakeKeyEvent (display, keycode, False, 0);
    XFlush(display);*/

    //XSync (display, False);

    //XTestGrabControl (display, False);
}
