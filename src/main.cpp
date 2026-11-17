#include <QApplication>
#include "../include/MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    if (w.mostrarWelcomeDialog()) {
        w.show();
        return app.exec();
    }

    return 0;
}
