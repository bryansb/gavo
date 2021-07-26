#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QImage>

#include <QDebug>

#include <cstdint>
#include <cstring>
#include <vector>

#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "./opencv_core.hpp"
#endif

#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

class QtScreenshot {
    public:
        QtScreenshot();
        void take(int x, int y, int w, int h, cv::Mat &out);

        QScreen *getScreen();
        void setScreen(QScreen *screen);

    private:
        QScreen *screen;
        QImage qpx_image;
};