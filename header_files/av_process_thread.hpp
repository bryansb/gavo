#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

#ifndef SCREENSHOT_INCLUDED
#define SCREENSHOT_INCLUDED
    #include "./qt_screenshot.hpp"
#endif

#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "./opencv_core.hpp"
#endif

#include <QThread>

class AVProcessThread : public QThread {
    private:

        const double WIDTH_SHOW = 600.0;

        double wResize;
        double hResize;

        int xPosition;
        int yPosition;
        int wSize;
        int hSize;

        Mat img;

        QtScreenshot *screenshot;
        
    public:
        bool running = false;
        
        AVProcessThread();
        void run();
        void stop();
        void setCaptureCoords(int x, int y, int w, int h);

        QtScreenshot * getScreenshot();

};