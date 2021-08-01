#include "../../../header_files/av_process_thread.hpp"

AVProcessThread::AVProcessThread() {
    this->screenshot = new QtScreenshot();
    this->inputSimulation = new InputSimulation();
    this->iterProcess = new IterProcess(inputSimulation);
    this->haarCascadeModel = new CascadeClassifier("../core/assets/cascade_model/cascade-final.xml");
    
}

void AVProcessThread::run() {
    if (this->running) namedWindow("Game Capture Detections", WINDOW_AUTOSIZE);

    while (this->running) {
        this->screenshot->take(xPosition, yPosition, wSize, hSize, this->img);
        Mat clon = img.clone();
        update(img, clon);
        
        if (waitKey(1) == 27) {
        }
        if (recording)
            outVideo->write(clon);
        cv::resize(clon, clon, cv::Size(abs(wResize), abs(hResize)));
       
        imshow("Game Capture Detections", clon);
    }
    destroyAllWindows();
}

void AVProcessThread::update(Mat &img, Mat &imgToPrint) {
    cvtColor(img, this->hsvImg, COLOR_RGB2HSV);
    bool isOnGame = detectIfIsOnGame(hsvImg);
    if ( isOnGame && gameStarted) {
        this->iterProcess->process(hsvImg, img, imgToPrint, true);
        haarCascadeProcess(img, imgToPrint, true);
    } else if (!isOnGame && gameStarted) {
        imwrite("end_capture.jpg", img);
        gameStarted = false;
        this->running = false;
        cout << "[INFO] Game over, image saved." << endl;
    } else if (isOnGame && !gameStarted) {
        gameStarted = true;

        imwrite("start_capture.jpg", img);
        cout << "[INFO] Game start, image saved." << endl;
    }
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
    cv::resize(frame, frame, cv::Size(abs(32), abs(32)));
    string path = "../corpus/samples/imgs_";
    string name = path+std::to_string(c)+".png";

    cv::imwrite(name, frame);
}

void AVProcessThread::haarCascadeProcess(Mat img, Mat &imgToPrint, bool print){
    vector<Rect> detections;
    haarCascadeModel->detectMultiScale(img, detections, 1.10, 4, 0, Size(30, 30), Size(40, 40));
    rectangle(imgToPrint, Point(MIN_DETECTION_HOLE, 290), Point(MAX_DETECTION_HOLE, 310), Scalar(127, 50, 170), 1);

    for (int i = 0; i < detections.size(); i++){
        cv::Rect hole = detections[i];
        if(print){
            rectangle(imgToPrint, hole.tl(), hole.br(), Scalar(0, 255, 0), 1);
        }
        if(hole.x >= MIN_DETECTION_HOLE && hole.x <= MAX_DETECTION_HOLE){
            inputSimulation->sendInput(UP_ARROW_KEYCODE);
        }
    }
}

void AVProcessThread::setRecording(bool recording, int w, int h) {
    if (recording && w > 0 && h > 0)
        outVideo = new VideoWriter( "./video_out.mkv", VideoWriter::fourcc('M','J','P','G'), 30, Size(w, h), true );
    this->recording = recording;
}

bool AVProcessThread::detectIfIsOnGame(Mat hsvImg) {
    Mat thresholdImg;
    cv::inRange(hsvImg, Scalar(inGameHsvMinMax[0], inGameHsvMinMax[1], inGameHsvMinMax[2]), 
                    Scalar(inGameHsvMinMax[3], inGameHsvMinMax[4], inGameHsvMinMax[5]), thresholdImg);

    if (countNonZero(thresholdImg) < 100) {
        return false;
    }
    return true;
}

void AVProcessThread::setGameStarted(bool gameStarted) {
    this->gameStarted = gameStarted;
    inputSimulation->sendInput(0x58);
}

QtScreenshot * AVProcessThread::getScreenshot() {
    return this->screenshot;
}