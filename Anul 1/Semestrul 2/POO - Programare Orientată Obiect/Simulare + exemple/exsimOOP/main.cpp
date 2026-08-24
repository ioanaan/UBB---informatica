#include "GUI.h"
#include "teste.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    testAll();
    QApplication app(argc, argv);
    FisierRepo repo{ "rochie.txt" };
    Service service{ repo };
    GUI gui{ service };
    gui.show();

    return app.exec();
}
