//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#include "ui.h"
#include <QApplication>
#include <QMessageBox>
#include "repoFisier.h"
#include "repoMemorie.h"
#include "cos.h"
#include "GUI.h"
#include "service.h"
#include "teste.h"
#include <iostream>

using std::cout;

/*
int main() {
    testAll();
        cout << "Testele au rulat cu succes!\n";

        if (_CrtDumpMemoryLeaks() == 1)
            printf("S-au gasit memory leaks\n");
        else
            printf("Nu avem memory leaks\n");

    UI ui;
    ui.run();
    return 0;
}
*/

int main(int argc, char *argv[]) {
    testAll();
    QApplication app(argc, argv);

    repoFisier repo{ "carti.txt" };
    Service serv{ repo };
    Cos cos{ serv };

    GUI gui{ serv, cos };
    gui.show();

    return app.exec();
}