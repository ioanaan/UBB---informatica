#include "GUI.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    FisierRepo repo{ "echipamente.txt" };
    Service service{ repo };
    GUI gui{ service };
    gui.show();

    return app.exec();
}
