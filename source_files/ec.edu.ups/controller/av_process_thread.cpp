#include "../../../header_files/av_process_thread.hpp"

AVProcessThread::AVProcessThread() {
    this->screenshot = new QtScreenshot();
    this->inputSimulation = new InputSimulation();

    model = readNetFromTensorflow(this->dnn_p, this->dnn_c);
}

void AVProcessThread::run() {
    if (this->running) namedWindow("Overview", WINDOW_AUTOSIZE);
    while (this->running) {
        this->screenshot->take(xPosition, yPosition, wSize, hSize, this->img);
        cv::resize(img, img, cv::Size(abs(300), abs(300)));

        Mat blob = dnn::blobFromImage(img, 1.0, img.size(),Scalar(104.0, 177.0, 123.0), true, false);
        model.setInput(blob);
        
        Mat detection = model.forward();

        Mat detectionMat(detection.size[2],detection.size[3],CV_32F,detection.ptr<float>());

        // cout << "Caras detectadas: " << detectionMat.rows << endl;

        Mat clon = img.clone();

        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

        // cout << detectionMat<< endl;

        float confianza = -1.0;
        for(int i=0;i<detectionMat.rows;i++){
            confianza = detectionMat.at<float>(i,2);

            if(confianza >= 0.5){ // Definims el umbral mínimo para detectar rostros [0.0, 1.0]
                x1 = static_cast<int> (detectionMat.at<float>(i, 3)*img.cols);
                y1 = static_cast<int> (detectionMat.at<float>(i, 4)*img.rows);
                x2 = static_cast<int> (detectionMat.at<float>(i, 5)*img.cols);
                y2 = static_cast<int> (detectionMat.at<float>(i, 6)*img.rows);

                rectangle(clon,Point(x1,y1),Point(x2,y2),Scalar(10,200,200),1.3);
            }
        }

        cv::resize(clon, clon, cv::Size(abs(wResize), abs(hResize)));
        imshow("Overview", clon);
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