#include <QThread>

#ifndef SYSINT_INCLUDED
#define SYSINT_INCLUDED
    #ifdef __unix__
        #include "./qt_screenshot.hpp"
        #include "./input_simulation.hpp"
        #define UP_ARROW_KEYCODE 0xFF52
    #elif defined(_WIN32) || defined(WIN32)
        #include "./input_simulation.hpp"
        #include "./qt_screenshot.hpp"
        #define UP_ARROW_KEYCODE 0x26
    #endif
#endif

#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "./opencv_core.hpp"
#endif

#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

#ifndef HUPROCESS_INCLUDED
#define HUPROCESS_INCLUDED
    #include "./iter_process.hpp"
#endif


class AVProcess : public QThread {
    private:

        const double WIDTH_SHOW = 600.0;

        const int MIN_DETECTION_HOLE = 200;
        const int MAX_DETECTION_HOLE = 400;

        int xMaxMove = 100;
        int xMove = 0;

        double moveBack = false;

        double wResize;
        double hResize;

        int xPosition;
        int yPosition;
        int wSize;
        int hSize;

        bool recording = false;
        bool gameStarted = false;

        int inGameHsvMinMax[6] = {71, 120, 152, 72, 121, 153};
        bool inGame;

        cv::Mat img;
        cv::Mat hsvImg;

        cv::CascadeClassifier *haarCascadeModel;
        VideoWriter *outVideo;

        IterProcess *iterProcess;
        QtScreenshot *screenshot;
        InputSimulation *inputSimulation;

        void update(Mat &img, Mat &imgToPrint);
        void saveSample(cv::Mat frame, int x, int y, int w, int h, int c);
        void haarCascadeProcess(Mat img, Mat &imgToPrint, bool print = false);
        bool detectIfIsOnGame(Mat hsvImg);

    public:
        bool running = false;
        
        AVProcess();
        void run() override;
        void stop();

        void setCaptureCoords(int x, int y, int w, int h);
        void setRecording(bool, int w, int h);

        void setGameStarted(bool);

        QtScreenshot * getScreenshot();

};