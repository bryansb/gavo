#include "../../../../../header_files/qt_screenshot.hpp"

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */
    #define OS_Windows 0
#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

    #define OS_Windows 1
#endif

QtScreenshot::QtScreenshot() {}

void QtScreenshot::take(int x, int y, int w, int h, cv::Mat &out) {

    if (!OS_Windows) {
        auto screens = QGuiApplication::screens();
        foreach (auto scr, screens) {
            qpx_image = scr->grabWindow(0, x, y, w, h).toImage().convertToFormat( QImage::Format_BGR888 );
        }
    }
    
    if (OS_Windows) {
        screen = QApplication::primaryScreen();
        qpx_image = screen->grabWindow(0, x, y, w, h).toImage().convertToFormat( QImage::Format_BGR888 );
    }
    out = cv::Mat(qpx_image.height(), qpx_image.width(),
            CV_8UC3,
            const_cast<uchar *>(qpx_image.bits()),
            static_cast<size_t>(qpx_image.bytesPerLine()))
        .clone();
}

QScreen *QtScreenshot::getScreen() {
    return this->screen;
}

void QtScreenshot::setScreen(QScreen *screen) {
    this->screen = screen;
}