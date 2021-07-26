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

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
    #define OS_Windows 0
#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

    #define OS_Windows 1
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