#include "../../../header_files/main_gui.hpp"

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    MainGUI *mainGUI = new MainGUI();

    return app.exec();
}