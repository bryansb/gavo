#include <QThread>

#ifndef SYSINT_INCLUDED
#define SYSINT_INCLUDED
    #ifdef __unix__
        #include "./qt_screenshot.hpp"
        #include "./input_simulation.hpp"
    #elif defined(_WIN32) || defined(WIN32)
        #include "./input_simulation.hpp"
        #include "./qt_screenshot.hpp"
    #endif
#endif

#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "./opencv_core.hpp"
#endif

#ifndef OPENCVDNN_INCLUDED
#define OPENCVDNN_INCLUDED
    #include <opencv2/dnn/dnn.hpp>
    #include <opencv2/dnn/all_layers.hpp>

    using namespace dnn;
#endif

#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif


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
        
        const string dnn_c = "../core/ts_files/frozen_inference_graph.pbtxt";
        const string dnn_p = "../core/ts_files/frozen_inference_graph.pb";

        dnn4_v20210301::Net model;

        
    public:
        bool running = false;
        
        AVProcessThread();
        void run() override;
        void stop();
        void setCaptureCoords(int x, int y, int w, int h);

        QtScreenshot * getScreenshot();

};