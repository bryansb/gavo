#include "../../../header_files/template_match_enemy.hpp"

TemplateMatchEnemy::TemplateMatchEnemy(){}

TemplateMatchEnemy::TemplateMatchEnemy(string name, int keyboardSignal, string imagePath){
    this->name = name;
    this->keyboardSignal = keyboardSignal;
    this->imagePath = imagePath;
}

bool TemplateMatchEnemy::loadImage(){
    this->image = imread(getImagePath());
    if (getImage().empty()) {
        cout << "[ERROR] " << getName() << " file not found: " << getImagePath() << endl;
        return false;
    } else {
        cout << "[INFO] " << getName() << " loaded " << endl;
    }
    return true;
}

string TemplateMatchEnemy::getName() {
    return name;
}

int TemplateMatchEnemy::getKeyboardSignal() {
    return keyboardSignal;
}

string TemplateMatchEnemy::getImagePath() {
    return imagePath;
}

Mat TemplateMatchEnemy::getImage() {
    return image;
}