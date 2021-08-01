#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMessageBox>

#ifndef AV_PROCESS_INCLUDED
#define AV_PROCESS_INCLUDED
    #include "./av_process_thread.hpp"
#endif

#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "./opencv_core.hpp"
#endif

#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

#include "./utils/hsv_threshold.hpp"

class MainGUI: public QMainWindow {
    protected:
        void closeEvent(QCloseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private slots:
        void handleMouseDetectButton();
        void handleRunButton();
        void handleStopButton();
        void handleHsvButton();
        void handleRecordButton();

    private:
        const QString APP_NAME = "G.A.V.O.";

        bool mouseCapEvent = false;
        bool firstCapMouse = true;
        bool areaCaptureSetted = false;
        bool gameCaptureShowed = false;
        bool readyToStart = false;

        bool recordGameplay = false;

        int xMousePosition;
        int yMousePosition;

        int widthCapture;
        int heightCapture;

        std::mutex frame_mutex;

        AVProcessThread * avProcessThread;

        HSVThreshold * hsvThreshold;

        // Qt Components
        QPushButton * mouseDetectButton;
        QPushButton * runButton;
        QPushButton * stopButton;
        QPushButton * recordButton;

        QPushButton * hsvButton;

        void initComponents();
        void startProcess();
        void stopProcess();
        void setRecordingStatus();

    public:
        MainGUI();

};