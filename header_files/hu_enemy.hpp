#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

#include "./utils/math_calcs.hpp"

class HuEnemy { 
    private: 
        string name;
        int keyboardSignal;
        double moments[7];
        int minHsv[3] = {0, 0, 0};
        int maxHsv[3] = {0, 0, 0};

    public:
        HuEnemy();
        HuEnemy(const string name, int keyboardSignal, double moments[7], 
                    int minHsv[3], int maxHsv[3]);
        string getName();
        int getKeyboardSignal();
        double *getMoments();

        int *getMinHsv();
        int *getMaxHsv();
};