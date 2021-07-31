#ifndef OPENCVCORE_INCLUDED
#define OPENCVCORE_INCLUDED
    #include "./opencv_core.hpp"
#endif

#ifndef CORE_INCLUDED
#define CORE_INCLUDED
    #include "./core.hpp"
#endif

class TemplateMatchEnemy {
    private:
        string name;
        int keyboardSignal;
        string imagePath;
        Mat image;

    public:
        TemplateMatchEnemy();
        TemplateMatchEnemy(string name, int keyboardSignal, string imagePath);

        bool loadImage();
        string getName();
        int getKeyboardSignal();
        string getImagePath();
        Mat getImage();

};