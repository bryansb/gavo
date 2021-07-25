#include "../../../../../header_files/main_gui.hpp"

// #include "../../../../../header_files/core.hpp"
// #include "../../../../../header_files/opencv_core.hpp"

// void ImageFromDisplay(std::vector<uint8_t>& Pixels, int& Width, int& Height, int& BitsPerPixel)
// {
//     Display* display = XOpenDisplay(nullptr);
//     Window root = DefaultRootWindow(display);

//     XWindowAttributes attributes = {0};
//     XGetWindowAttributes(display, root, &attributes);

//     Width = attributes.width/4;
//     Height = attributes.height/4;

//     XImage* img = XGetImage(display, root, 0, 0, Width, Height, AllPlanes, ZPixmap);
//     BitsPerPixel = img->bits_per_pixel;
//     Pixels.resize(Width * Height * 4);

//     memcpy(&Pixels[0], img->data, Pixels.size());

//     XDestroyImage(img);
//     XCloseDisplay(display);
// }

int main(int argc, char* argv[]) {
    // int Width = 0;
    // int Height = 0;
    // int Bpp = 0;
    // std::vector<std::uint8_t> Pixels;

    // ImageFromDisplay(Pixels, Width, Height, Bpp);

    // if (Width && Height)
    // {
    //     Mat img = Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); //Mat(Size(Height, Width), Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]); 

    //     namedWindow("Display window", WINDOW_AUTOSIZE);
    //     imshow("Display window", img);

    //     waitKey(0);
    // }

    // QApplication app(argc, argv);

    // QtScreenshot *s = new QtScreenshot();
    // Mat img;

    // namedWindow("Display window", WINDOW_AUTOSIZE);

    // while(true) {
    //     s->take(500, 500, 500, 500, img);
    //     imshow("Display window", img);
    //     if (waitKey(1) == 27){
    //         break;
    //     }
    // }

    // waitKey(0);


    QApplication *app = new QApplication(argc, argv);
    MainGUI *mainGUI = new MainGUI(app);

    // app.desktop().screenNumber();

    return app->exec();
}