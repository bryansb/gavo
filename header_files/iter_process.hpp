#ifndef SYSINT_INCLUDED
#define SYSINT_INCLUDED
    #ifdef __unix__
        #include "./qt_screenshot.hpp"
        #include "./input_simulation.hpp"
    #elif defined(_WIN32) || defined(WIN32)
        #include "./input_simulation.hpp"
        #include "./qt_screenshot.hpp"
    #endif
#endif

#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "./opencv_core.hpp"
#endif

#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

#include "./hu_enemy.hpp"
#include "./template_match_enemy.hpp"

#ifndef UMBRAL_DETECTION
#define UMBRAL_DETECTION 0.04
#endif

class IterProcess {
    private:
        int maxWidthProcess = 321;
        int maxHeightProcess = 257;
        int stepIter = 64;

        int huEnemySize;
        int templateMatchEnemySize;
        vector<HuEnemy> huEnemyVector;
        vector<TemplateMatchEnemy> templateMatchVector;

        Moments momentsOut;
        InputSimulation *inputSimulation;
        
        void initHuEnemy();
        void initTemplateMatchEnemy();
        void huProcess(Mat hsvImg, Mat &imgToPrint, HuEnemy huEnemy, int i, int j, bool print = false);
        void templateMatchProcess(Mat img, Mat &imgToPrint, TemplateMatchEnemy templateMatchEnemy, 
                                    int i, int j, bool print = false);

    public:
        IterProcess(InputSimulation *inputSimulation);
        void process(Mat hsvImg, Mat img, Mat &imgToPrint, bool print = false);
};