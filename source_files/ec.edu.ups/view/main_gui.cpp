#include "../../../header_files/main_gui.hpp"

MainGUI::MainGUI() {
    this->avProcess = new AVProcess();
    this->hsvThreshold = new HSVThreshold();
    this->initComponents();
}

void MainGUI::initComponents() {
    this->resize(300, 100);
    this->setWindowTitle(APP_NAME); //QString::fromStdString(
    QWidget *widget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(widget);
    widget->setLayout(layout);
    this->setCentralWidget(widget);

    // Mouse Widget
    QWidget *mouseWidget = new QWidget(widget);
    QHBoxLayout *mouseWidgetLayout = new QHBoxLayout(mouseWidget);
    mouseWidget->setLayout(mouseWidgetLayout);

    this->mouseDetectButton = new QPushButton("Set Capture Area", mouseWidget);
    connect(mouseDetectButton, &QPushButton::released,this, &MainGUI::handleMouseDetectButton);
    mouseWidgetLayout->addWidget(mouseDetectButton);

    layout->addWidget(mouseWidget, 0, 0, 1, 1);
    // Mouse Widget //

    // Run Widget
    QWidget *runWidget = new QWidget(widget);
    QHBoxLayout *runWidgetLayout = new QHBoxLayout(runWidget);
    runWidget->setLayout(runWidgetLayout);

    this->runButton = new QPushButton("Run", runWidget);
    connect(runButton, &QPushButton::released,this, &MainGUI::handleRunButton);
    runWidgetLayout->addWidget(runButton);
    this->runButton->setDisabled(true);

    this->stopButton = new QPushButton("Stop", runWidget);
    stopButton->setVisible(false);
    connect(stopButton, &QPushButton::released,this, &MainGUI::handleStopButton);
    runWidgetLayout->addWidget(stopButton);

    layout->addWidget(runWidget, 1, 0, 1, 1);
    // Run Widget //

    // Record Widget
    QWidget *recordWidget = new QWidget(widget);
    QHBoxLayout *recordWidgetLayout = new QHBoxLayout(recordWidget);
    recordWidget->setLayout(recordWidgetLayout);

    this->recordButton = new QPushButton("Record", recordWidget);
    connect(recordButton, &QPushButton::released,this, &MainGUI::handleRecordButton);
    recordButton->setDisabled(true);
    recordWidgetLayout->addWidget(recordButton);

    layout->addWidget(recordWidget, 2, 0, 1, 1);
    // Record Widget //

    // HSV Widget
    QWidget *hsvWidget = new QWidget(widget);
    QHBoxLayout *hsvWidgetLayout = new QHBoxLayout(hsvWidget);
    hsvWidget->setLayout(hsvWidgetLayout);

    this->hsvButton = new QPushButton("Thresholding Tool", hsvWidget);
    connect(hsvButton, &QPushButton::released,this, &MainGUI::handleHsvButton);
    hsvButton->setDisabled(true);
    hsvWidgetLayout->addWidget(hsvButton);

    layout->addWidget(hsvWidget, 3, 0, 1, 1);

    // HSV Widget //

    // Detect when main window lost focus
    QObject::connect(qApp, &QGuiApplication::applicationStateChanged, this, [=](Qt::ApplicationState state){
        // qDebug() << state;
        
    });

    this->show();
}

void MainGUI::setRecordingStatus() {
    if ( !this->recordGameplay ) {
        this->recordButton->setText("Record");
        this->avProcess->setRecording(false, 0, 0);
    } else {
        this->recordButton->setText("Stop Recording");
        this->avProcess->setRecording(true, widthCapture, heightCapture);
        
    }
}

void MainGUI::startProcess() {
    this->avProcess->running = this->areaCaptureSetted;
    this->gameCaptureShowed = true;
    this->avProcess->run();

    stopProcess();
    stopButton->setVisible(false);
    runButton->setVisible(true);
    recordButton->setDisabled(true);
}

void MainGUI::stopProcess() {
    this->avProcess->stop();
    this->readyToStart = false;
    this->gameCaptureShowed = false;
    this->recordGameplay = false;
    setRecordingStatus();
}

// Events

void MainGUI::mouseReleaseEvent(QMouseEvent *event) {
    if (this->mouseCapEvent) {
        int x = event->globalX();
        int y = event->globalY();
        this->xMousePosition = x;
        this->yMousePosition = y;
        this->widthCapture = 620;
        this->heightCapture = 415;
        this->avProcess->setCaptureCoords(this->xMousePosition, this->yMousePosition, 
            this->widthCapture, this->heightCapture);
        this->mouseCapEvent = false;
        this->areaCaptureSetted = true;
        this->mouseDetectButton->setDisabled(false);
        this->runButton->setDisabled(false);
        this->hsvButton->setDisabled(false);
    }

}

void MainGUI::closeEvent (QCloseEvent *event){
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                tr("¿Está seguro?"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        stopProcess();
        event->accept();
    }
}

// Slots
void MainGUI::handleMouseDetectButton() {
    this->mouseCapEvent = true;
    this->mouseDetectButton->setDisabled(true);
    this->runButton->setDisabled(true);
}

void MainGUI::handleRunButton() {
    if (this->areaCaptureSetted) {
        runButton->setVisible(false);
        stopButton->setVisible(true);
        recordButton->setDisabled(false);
        startProcess();
        // this->avProcessThread->setGameStarted(true);
    }
}

void MainGUI::handleStopButton() {
    stopProcess();
    stopButton->setVisible(false);
    runButton->setVisible(true);
    recordButton->setDisabled(true);
    destroyAllWindows();
}

void MainGUI::handleHsvButton() {
    QtScreenshot s;
    Mat img;
    s.take(xMousePosition, yMousePosition, widthCapture, heightCapture, img);
    this->hsvThreshold->initComponents(img);
}

void MainGUI::handleRecordButton() {
    this->recordGameplay = this->recordGameplay ? false : true;
    setRecordingStatus();
}