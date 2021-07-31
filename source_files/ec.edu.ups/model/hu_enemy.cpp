#include "../../../header_files/hu_enemy.hpp"

HuEnemy::HuEnemy(){}

HuEnemy::HuEnemy(const string name, int keyboardSignal, double moments[7], 
                    int minHsv[3], int maxHsv[3]){
    this->name = name;
    this->keyboardSignal = keyboardSignal;
    for (int i = 0; i < 7; i++){
        this->moments[i] = moments[i];
    }

    for (int i = 0; i < 3; i++) {
        this->minHsv[i] = minHsv[i];
        this->maxHsv[i] = maxHsv[i];
    }
}

string HuEnemy::getName() {
    return name;
}

int HuEnemy::getKeyboardSignal() {
    return keyboardSignal;
}

double *HuEnemy::getMoments() {
    return moments;
}

int *HuEnemy::getMinHsv() {
    return minHsv;
}

int *HuEnemy::getMaxHsv() {
    return maxHsv;
}