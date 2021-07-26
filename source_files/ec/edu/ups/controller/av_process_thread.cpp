#include "../../../../../header_files/av_process_thread.hpp"

AVProcessThread::AVProcessThread() {
    this->screenshot = new QtScreenshot();
    this->inputSimulation = new InputSimulation();
}

void AVProcessThread::run() {
    if (this->running) namedWindow("Overview", WINDOW_AUTOSIZE);
    while (this->running) {
        // this->screenshot->take(this->x, this->y, 
        //     this->w, this->h, this->img);
        this->screenshot->take(xPosition, yPosition, wSize, hSize, this->img);
        
        cv::resize(img, img, cv::Size(abs(wResize), abs(hResize)));
        inputSimulation->sendInput(0x41);
        imshow("Overview", img);
        if (waitKey(1) == 27){
            // this->running = false;
            // SendInput();
        }
     }
     destroyAllWindows();
}

void AVProcessThread::stop() {
    this->running = false;
    this->wait();
}

void AVProcessThread::setCaptureCoords(int x, int y, int w, int h){
        this->wSize = w;
        this->hSize = h;
        this->xPosition = x;
        this->yPosition = y;

        this->wResize = WIDTH_SHOW;
        this->hResize = (this->wResize / w) * h;
}

QtScreenshot * AVProcessThread::getScreenshot() {
    return this->screenshot;
}