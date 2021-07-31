#include "../../../header_files/utils/hsv_threshold.hpp"

HSVThreshold::HSVThreshold() {
    this->imgMoments = Moments();
}

void HSVThreshold::initComponents(Mat img) {
    this->img = img;
    cv::cvtColor(img, hsv, COLOR_RGB2HSV);
    namedWindow("Imagen Original", WINDOW_AUTOSIZE);
    namedWindow("Imagen HSV", WINDOW_AUTOSIZE);
    namedWindow("Imagen Umbralizado", WINDOW_AUTOSIZE);

    imshow("Imagen Original", img);
    imshow("Imagen HSV", hsv);

    CalcMoments calcMoments = {thresholdImg, imgMoments};
    setMouseCallback("Imagen Umbralizado", mouseEventCV, (void*)&calcMoments);

    TrackParams tp = {93, 105 , 22, 99, 126, 214, img, hsv, thresholdImg, baseMoments, huMomentsOut};

    createTrackbar("Min-H","Imagen Original",&tp.minH, 180, functionTrackbarHSV, (void*)&tp);
    createTrackbar("Min-S","Imagen Original",&tp.minS, 255, functionTrackbarHSV, (void*)&tp);
    createTrackbar("Min-V","Imagen Original",&tp.minV, 255, functionTrackbarHSV, (void*)&tp);

    createTrackbar("Max-H","Imagen Original",&tp.maxH, 180, functionTrackbarHSV, (void*)&tp);
    createTrackbar("Max-S","Imagen Original",&tp.maxS, 255, functionTrackbarHSV, (void*)&tp);
    createTrackbar("Max-V","Imagen Original",&tp.maxV, 255, functionTrackbarHSV, (void*)&tp);

    waitKey(0);
}

double HSVThreshold::euclidenDistance(double hu1[7], double hu2[7]) {
    double d = 0.0;
    for(int i = 0; i < 7; i++) {
        d += (hu1[i] - hu2[i]) * (hu1[i] - hu2[i]);
    }

    return sqrt(d);
}

void HSVThreshold::functionTrackbarHSV(int v, void *param){
    TrackParams* tp = (TrackParams*) param;
    cv::inRange(tp->hsv, Scalar(tp->minH, tp->minS, tp->minV), Scalar(tp->maxH, tp->maxS, tp->maxV), tp->thresholdImg);
    cv::imshow("Imagen Umbralizado", tp->thresholdImg);

    cv::inRange(tp->hsv, Scalar(tp->minH, tp->minS, tp->minV), Scalar(tp->maxH, tp->maxS, tp->maxV), tp->thresholdImg);

    // Rect r(0, 0, 64, 64);
    // Mat subimg = tp->thresholdImg(r);

    int w = 384;
    int h = 320;

    Moments momentsOut;

    for (int i = 0; i < h; i += 32) {
        for (int j = 0; j < w; j += 32) {
            Rect r(j, i, 64, 64);
            Mat subimg = tp->thresholdImg(r);

            // imshow("Sub", subimg);
            // waitKey(60);

            momentsOut = moments(subimg, true);
            HuMoments(momentsOut, tp->huMomentsOut);
            double distance = HSVThreshold::euclidenDistance(tp->huMomentsOut, tp->baseMoments);
            // cout << "[INFO] Distance:" << distance << endl;

            if ( distance < UMBRAL) {
                double cx = momentsOut.m10/momentsOut.m00;
                double cy = momentsOut.m01/momentsOut.m00;

                circle(tp->img, Point((int) cx + j, (int)cy + i), 17, Scalar(1, 1, 255), 3);
                putText(tp->img, "Detectado",Point((int)cx + j, (int)cy + 23 + i), FONT_HERSHEY_SIMPLEX, 1, Scalar(10, 200, 200));
            }
        }    
    }
    cv::imshow("Imagen Original", tp->img);
}

void HSVThreshold::mouseEventCV(int event, int x, int y, int flags, void *param) {
    if (event == EVENT_LBUTTONDOWN){
        CalcMoments* calcM = (CalcMoments*)param;
        calcM->imgMoments = moments(calcM->thresholdImg, true);
        double huMoments[7];
        HuMoments(calcM->imgMoments, huMoments);
        cout << "{";
        for(int i = 0; i < 7; i++) {
            cout << huMoments[i];
            if (i != 6) {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
}