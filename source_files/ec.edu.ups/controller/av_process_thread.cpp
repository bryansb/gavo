#include "../../../header_files/av_process_thread.hpp"

AVProcessThread::AVProcessThread() {
    this->screenshot = new QtScreenshot();
    this->inputSimulation = new InputSimulation();
    this->haarCascadeModel = CascadeClassifier("../corpus/classifier/cascade.xml");
    
}

void AVProcessThread::run() {
    if (this->running) namedWindow("Overview", WINDOW_AUTOSIZE);
    // auto model = readNetFromTensorflow(this->dnn_p, this->dnn_c);

    int counter = 0;
    vector<double> weights;
    vector<int> levels;
    vector<Rect> detections;

    while (this->running) {
        this->screenshot->take(xPosition, yPosition, wSize, hSize, this->img);
        // cv::resize(img, img, cv::Size(abs(300), abs(300)));
        Mat clon = img.clone();
        
        if (waitKey(1) == 27){
            // this->running = false;
            // SendInput();
            
        }
        cv::resize(clon, clon, cv::Size(abs(wResize), abs(hResize)));
        imshow("Overview", clon);
        // waitKey(0);
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

void AVProcessThread::saveSample(cv::Mat frame, int x, int y, int w, int h, int c){
    Rect frameRect(x+1, y+1, w-1, h-1);
    frame = frame(frameRect);
    string path = "../corpus/p/imgp_";
    string name = path+std::to_string(c)+".png";

    cv::imwrite(name, frame);
}

QtScreenshot * AVProcessThread::getScreenshot() {
    return this->screenshot;
}