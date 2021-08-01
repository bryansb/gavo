#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "../opencv_core.hpp"
#endif

#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "../core.hpp"
#endif

#ifndef UMBRAL
#define UMBRAL 0.04
#endif

struct TrackParams {
    int minH;
    int minS;
    int minV;

    int maxH;
    int maxS;
    int maxV;

    Mat &img;
    Mat &hsv;
    Mat &thresholdImg;

    double *baseMoments;
    double *huMomentsOut;
};

struct CalcMoments {
    Mat &thresholdImg;
    Moments &imgMoments;
};

class HSVThreshold {
    private:
        Moments imgMoments;
        // CalcMoments calcMoments;
        // TrackParams tp;
        Mat img;
        Mat hsv;
        Mat thresholdImg;

        //Nave amarilla: 0.234379,0.0267877,0.000239247,2.49708e-05,-1.93007e-09,-4.08697e-06,-2.7341e-19

        double baseMoments[7] = {0.234379,0.0267877,0.000239247,2.49708e-05,-1.93007e-09,-4.08697e-06,-2.7341e-19};
        double huMomentsOut[7];

        static double euclidenDistance(double hu1[7], double hu2[7]);
        static void functionTrackbarHSV(int v, void *p);
        static void mouseEventCV(int event, int x, int y, int flags, void *param);
        // void 
    public:
        HSVThreshold();
        void initComponents(Mat img);
};