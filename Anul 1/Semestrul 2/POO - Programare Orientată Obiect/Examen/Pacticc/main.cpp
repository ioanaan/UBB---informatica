#include <QApplication>
#include "GUI.h"
#include "teste.h"

int main(int argc, char* argv[]) {

    runAllTests();

    QApplication a(argc, argv);
    GUI w;
    w.show();
    return a.exec();
}
