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

#ifndef HUPROCESS_INCLUDED
#define HUPROCESS_INCLUDED
    #include "./iter_process.hpp"
#endif


class AVProcessThread : public QThread {
    private:

        const double WIDTH_SHOW = 600.0;

        int xMaxMove = 100;
        int xMove = 0;

        double moveBack = false;

        double wResize;
        double hResize;

        int xPosition;
        int yPosition;
        int wSize;
        int hSize;

        cv::Mat img;
        cv::Mat hsvImg;

        QtScreenshot *screenshot;
        InputSimulation *inputSimulation;

        cv::CascadeClassifier haarCascadeModel;

        IterProcess *iterProcess;

        const string dnn_c = "../core/ts_files/frozen_inference_graph.pbtxt";
        const string dnn_p = "../core/ts_files/frozen_inference_graph.pb";

        void update(Mat &img, Mat &imgToPrint);
    public:
        bool running = false;
        
        AVProcessThread();
        void run() override;
        void stop();
        void setCaptureCoords(int x, int y, int w, int h);
        void saveSample(cv::Mat frame, int x, int y, int w, int h, int c);

        QtScreenshot * getScreenshot();

};