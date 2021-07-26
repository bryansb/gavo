#ifndef SYSINT_INCLUDED
#define SYSINT_INCLUDED
    #include "./input_simulation.hpp"
    #include "./qt_screenshot.hpp"
#endif

#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "./opencv_core.hpp"
#endif

#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
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

        cv::Mat img;

        QtScreenshot *screenshot;
        InputSimulation *inputSimulation;

        
    public:
        bool running = false;
        
        AVProcessThread();
        void run();
        void stop();
        void setCaptureCoords(int x, int y, int w, int h);

        QtScreenshot * getScreenshot();

};