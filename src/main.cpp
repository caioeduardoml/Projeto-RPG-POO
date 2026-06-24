#include <QApplication>
#include "../include/MainWindow.hpp"
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[]) {
    srand(time(0));

    QApplication app(argc, argv);

    MainWindow w;
    if (w.mostrarWelcomeDialog()) {
        w.show();
        return app.exec();
    }

    return 0;
}
