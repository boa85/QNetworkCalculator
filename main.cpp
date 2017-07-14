
#include <QApplication>
#include "gui/include/main_window.h"

using namespace calculator;
using namespace gui;

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    return application.exec();
}