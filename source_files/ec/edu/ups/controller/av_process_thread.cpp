#include "../../../../../header_files/av_process_thread.hpp"

AVProcessThread::AVProcessThread() {
    this->screenshot = new QtScreenshot();
}

void AVProcessThread::run() {
    if (this->running) namedWindow("Overview", WINDOW_AUTOSIZE);
    while (this->running) {
        this->screenshot->take(this->x, this->y, 
            this->w, this->h, this->img);
        
        cv::resize(img, img, Size(abs(wResize), abs(hResize)));
        imshow("Overview", img);
        if (waitKey(1) == 27){
            // this->running = false;
        }
     }
     destroyAllWindows();
}

void AVProcessThread::stop() {
    this->running = false;
    this->wait();
}

void AVProcessThread::setCaptureCoords(int x, int y, int w, int h){
        this->w = w;
        this->h = h;
        this->x = x;
        this->y = y;

        this->wResize = WIDTH_SHOW;
        this->hResize = (this->wResize / w) * h;
}

QtScreenshot * AVProcessThread::getScreenshot() {
    return this->screenshot;
}