#include "../../../header_files/iter_process.hpp"

IterProcess::IterProcess(InputSimulation *inputSimulation) {
    this->inputSimulation = inputSimulation;
    initHuEnemy();
    initTemplateMatchEnemy();
    this->huEnemySize = (int)this->huEnemyVector.size();
    this->templateMatchEnemySize = (int)this->templateMatchVector.size();
}

void IterProcess::initHuEnemy(){
    double yellowMoments[7] = {0.234379, 0.0267877, 0.000239247, 2.49708e-05,
                                -1.93007e-09, -4.08697e-06, -2.7341e-19};
    int minHsvYellow[3] = {93, 105 , 22};
    int maxHsvYellow[3] = {99, 126, 214};
    HuEnemy yellow("Yellow Spaceship", 0x58, yellowMoments, minHsvYellow, maxHsvYellow);

    double pinkMoments[7] = {0.314188, 0.0402822, 0.0130514,0.00107905, 
                                -3.91635e-06, -0.000212291, -1.02957e-06};
    int minHsvPink[3] = {138, 92 , 79};
    int maxHsvPink[3] = {145, 99, 210};
    HuEnemy pink("Pink Spaceship", 0x58, pinkMoments, minHsvPink, maxHsvPink);
    this->huEnemyVector.push_back(pink);

    double rockMoments[7] = {0.230399, 0.0174037, 0.0047436, 0.00020321,
                                -1.96732e-07, -2.62348e-05, -3.31995e-08};
    int minHsvRock[3] = {95, 138, 109};
    int maxHsvRock[3] = {103, 174, 156};
    HuEnemy rock("Rock", 0x58, rockMoments, minHsvRock, maxHsvRock);
    this->huEnemyVector.push_back(rock);

    double whiteMoments[7] = {0.401657, 0.0312864, 0.0294343, 0.00165361, 4.29646e-06, 2.09922e-05, -1.07066e-05};
    int minHsvWhite[3] = {0, 0, 110};
    int maxHsvWhite[3] = {0, 0, 255};
    HuEnemy white("White Spaceship", 0x58, whiteMoments, minHsvWhite, maxHsvWhite);
    this->huEnemyVector.push_back(white);
}

void IterProcess::initTemplateMatchEnemy() {
    TemplateMatchEnemy yellowEnemy1("Yellow spaceship 1", 0x58, "../core/assets/tm_models/yellow_ship_model1.jpg");
    yellowEnemy1.loadImage();

    // this->templateMatchVector.push_back(yellowEnemy1);

    TemplateMatchEnemy yellowEnemy2("Yellow spaceship 2", 0x58, "../core/assets/tm_models/yellow_ship_model2.jpg");
    yellowEnemy2.loadImage();

    this->templateMatchVector.push_back(yellowEnemy2);

    TemplateMatchEnemy yellowEnemy3("Yellow spaceship 3", 0x58, "../core/assets/tm_models/yellow_ship_model3.jpg");
    yellowEnemy3.loadImage();

    this->templateMatchVector.push_back(yellowEnemy3);
}

void IterProcess::process(Mat hsvImg, Mat img, Mat &imgToPrint, bool print) {
    Rect r;
    Mat subimgHsv;
    Mat subImg;
    for (int i = 0; i < maxHeightProcess; i += stepIter) {
        for (int j = 0; j < maxWidthProcess; j += stepIter) {
            r = Rect(j, i, 64, 64);
            subimgHsv = hsvImg(r);
            subImg = img(r);
            for (HuEnemy &huEnemy : huEnemyVector) {
                huProcess(subimgHsv, imgToPrint, huEnemy, i, j, print);
            }
            for (TemplateMatchEnemy &templateMatchEnemy : templateMatchVector) {
                templateMatchProcess(subImg, imgToPrint, templateMatchEnemy, i, j, print);
            }
        }

    }
}

void IterProcess::huProcess(Mat subimg, Mat &imgToPrint, HuEnemy huEnemy, int i, int j, bool print) {
    double huMomentsOut[7];
    double distance = 0.0;

    int *minHsv = huEnemy.getMinHsv();
    int *maxHsv = huEnemy.getMaxHsv();

    Mat thresholdImg;
    cv::inRange(subimg, Scalar(minHsv[0], minHsv[1], minHsv[2]), 
                    Scalar(maxHsv[0], maxHsv[1], maxHsv[2]), thresholdImg);
    
    momentsOut = moments(thresholdImg, true);
    HuMoments(momentsOut, huMomentsOut);
    distance = MathCalcs::euclideanDistance(huMomentsOut, huEnemy.getMoments());
    if ( distance < UMBRAL_DETECTION) {
        inputSimulation->sendInput(huEnemy.getKeyboardSignal());
        if (print) {
            double cx = momentsOut.m10/momentsOut.m00;
            double cy = momentsOut.m01/momentsOut.m00;
            circle(imgToPrint, Point((int) cx + j, (int)cy + i), 20, Scalar(240, 240, 150), 2);
            // putText(img, huEnemy.getName(), Point((int)cx + j, (int)cy - 23 + i), 
            //             FONT_HERSHEY_SIMPLEX, 1, Scalar(10, 200, 200));
        }
    }
}
void IterProcess::templateMatchProcess(Mat subimg, Mat &imgToPrint, TemplateMatchEnemy templateMatchEnemy, 
                                        int i, int j, bool print) {
    Mat result;

    matchTemplate(subimg, templateMatchEnemy.getImage(), result, TM_SQDIFF_NORMED);
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    double minValue = 0.0, maxValue = 0.0;
    Point locMinima, locMaxima;
    minMaxLoc(result, &minValue, &maxValue, &locMinima, &locMaxima, Mat());
    // cout << maxValue << " | " << minValue << endl;
    if (minValue < -1.00000e-08) {
        inputSimulation->sendInput(templateMatchEnemy.getKeyboardSignal());
        // cout << minValue << endl;
        if (print) {
            locMinima.x += j;
            locMinima.y += i;
            
            rectangle(imgToPrint, locMinima,
                Point(locMinima.x + templateMatchEnemy.getImage().cols, 
                        locMinima.y + templateMatchEnemy.getImage().rows),
                Scalar(0, 200, 200), 2);
        }
    }
    
}   
