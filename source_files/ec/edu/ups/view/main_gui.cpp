#include "../../../../../header_files/main_gui.hpp"

MainGUI::MainGUI() {
    this->avProcessThread = new AVProcessThread();
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

    this->mouseDetectButton = new QPushButton("Establecer Area", mouseWidget);
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

    this->stopButton = new QPushButton("Stop", runWidget);
    stopButton->setVisible(false);
    connect(stopButton, &QPushButton::released,this, &MainGUI::handleStopButton);
    runWidgetLayout->addWidget(stopButton);

    layout->addWidget(runWidget, 1, 0, 1, 1);
    // Run Widget //
    

    this->show();
}

void MainGUI::startProcess() {
    this->avProcessThread->running = this->areaCaptureSetted;
    this->avProcessThread->run();
}

void MainGUI::stopProcess() {
    this->avProcessThread->stop();
}

// Events
void MainGUI::mouseMoveEvent(QMouseEvent *event) {
}

void MainGUI::mouseReleaseEvent(QMouseEvent *event) {
    // qDebug() << event->globalPos();
    // qDebug() << event->globalX();
    // qDebug() << event->globalY();
    if (this->mouseCapEvent) {
        int x = event->globalX();
        int y = event->globalY();

        if (this->firstCapMouse) {
            this->xMousePosition = x;
            this->yMousePosition = y;
            this->firstCapMouse = false;
            this->areaCaptureSetted = false;
        } else {
            this->widthCapture = abs(x - this->xMousePosition);
            this->heightCapture = abs(y - this->yMousePosition);

            this->avProcessThread->setCaptureCoords(this->xMousePosition, this->yMousePosition, 
                this->widthCapture, this->heightCapture);

            this->mouseCapEvent = false;
            this->firstCapMouse = true;
            this->areaCaptureSetted = true;
            this->mouseDetectButton->setDisabled(false);
            this->runButton->setDisabled(false);

            qDebug() << "[INFO] Capture Area X:" << this->xMousePosition << " | Y:" <<  this->yMousePosition << " | W:" << 
                 this->widthCapture << " | H:" << this->heightCapture; 
        }
    }
    // QPoint globalCursorPos = QCursor::pos();
    // int mouseScreen = this->app->desktop()->screenNumber(globalCursorPos);

    // QRect mouseScreenGeometry = qApp->desktop()->screen(mouseScreen)->geometry();
    // QPoint localCursorPos = globalCursorPos - mouseScreenGeometry.topLeft();
    // qDebug() << localCursorPos;

}

void MainGUI::closeEvent (QCloseEvent *event){
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, APP_NAME,
                                                                tr("¿Está seguro?\n"),
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
        startProcess();
    }
}

void MainGUI::handleStopButton() {
    stopProcess();
    stopButton->setVisible(false);
    runButton->setVisible(true);
}